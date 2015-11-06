#include "MaterialSmoothing.h"
#include "MooseError.h"

template<>
InputParameters validParams<MaterialSmoothing>()
{
  InputParameters params = validParams<InternalSideUserObject>();
  // Smoothing function
  params.addParam<std::string>("smoothing_fct_name", "invalid", "Name of the smoothing function to use.");
  // Coupled variables
  params.addRequiredCoupledVar("variable", "the variable name this userobject is acting on.");  
  params.addRequiredParam<std::string>("var_name", "the name of the variable that will store the smoothed variable.");

  return params;
}

MaterialSmoothing::MaterialSmoothing(const std::string & name, InputParameters parameters) :
    InternalSideUserObject(name, parameters),
    // Smoothing function
    _smthg_fct_type("max min average invalid", getParam<std::string>("smoothing_fct_name")),
    _aux(_fe_problem.getAuxiliarySystem()),
    // Coupled variables
    _u(coupledValue("variable")),
    _u_neighbor(coupledNeighborValue("variable")),
    _var_name(getParam<std::string>("var_name")),
    _value(0.)
{}

MaterialSmoothing::~MaterialSmoothing()
{
}

void
MaterialSmoothing::initialize()
{
  NumericVector<Number> & sln = _aux.solution();
  _aux.system().zero_variable(sln, _aux.getVariable(_tid, _var_name).number());
}

void
MaterialSmoothing::execute()
{
  int dim = _mesh.dimension();
  dof_id_type dof_nb_aux = _current_elem->n_dofs(_aux.number(), _fe_problem.getVariable(_tid, _var_name).number());
  dof_id_type dof_nb = 0.;
  dof_id_type dof_nb_neighbor = 0.;

  if (dof_nb_aux != 0) {
    _value = 0.;
    NumericVector<Number> & sln = _aux.solution();

    // Determine the degree of freedom:
    dof_nb = _current_elem->dof_number(_aux.number(), _fe_problem.getVariable(_tid, _var_name).number(), 0);
    dof_nb_neighbor = _neighbor_elem->dof_number(_aux.number(), _fe_problem.getVariable(_tid, _var_name).number(), 0);

    // Loop over the quadrature points
    for (unsigned int qp = 0; qp < _q_point.size(); ++qp)
    {
      Real value_temp = 0.;
      switch (_smthg_fct_type)
      {
        case 0: // max
          value_temp = std::max(_u[qp], _u_neighbor[qp]);
          _value = std::max(value_temp, _value);
          break;
        case 1: // min
          value_temp = std::min(_u[qp], _u_neighbor[qp]);
          _value = std::min(value_temp, _value);
          break;
        case 2: // average
          value_temp = 0.5*(_u[qp]+_u_neighbor[qp]);
          _value *= 0.5;
          _value += 0.5*value_temp;
          break;
        default: // invalid
          mooseError("Invalid smoothing function used in "<<name()<<".");
          break;
      }
    }

    // Set the value:
    if (_smthg_fct_type==2)
    {
      sln.add(dof_nb, 2*_value);
//      sln.add(dof_nb_neighbor, _value*0.5);
    }
    else
      sln.add(dof_nb, _value);
  }

}

void
MaterialSmoothing::destroy()
{
}

void
MaterialSmoothing::finalize()
{
  _aux.solution().close();
}

void
MaterialSmoothing::threadJoin(const UserObject & uo)
{
}