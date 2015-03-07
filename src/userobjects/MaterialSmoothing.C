#include "MaterialSmoothing.h"
#include "MooseError.h"

template<>
InputParameters validParams<MaterialSmoothing>()
{
  InputParameters params = validParams<InternalSideUserObject>();

  params.addRequiredCoupledVar("variable", "the variable name this userobject is acting on.");  
  params.addRequiredParam<std::string>("var_name", "the name of the variable that will store the smoothed variable.");

  return params;
}

MaterialSmoothing::MaterialSmoothing(const std::string & name, InputParameters parameters) :
    InternalSideUserObject(name, parameters),
    _aux(_fe_problem.getAuxiliarySystem()),
    _grad_u(coupledGradient("variable")),
    _grad_u_neighbor(coupledNeighborGradient("variable")),
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

    for (unsigned int qp = 0; qp < _q_point.size(); ++qp)
    {
      Real _value_temp = 0.5*(_grad_u[qp](0)+_grad_u_neighbor[qp](0));
      _value = std::max(_value_temp, _value);
    }

    // Determine the degree of freedom:
    dof_nb = _current_elem->dof_number(_aux.number(), _fe_problem.getVariable(_tid, _var_name).number(), 0);
    dof_nb_neighbor = _neighbor_elem->dof_number(_aux.number(), _fe_problem.getVariable(_tid, _var_name).number(), 0);

    // Set the value:
    sln.add(dof_nb, _value*0.5);
    sln.add(dof_nb_neighbor, _value*0.5);
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