#include "TimeStepCFL.h"

template<>
InputParameters validParams<TimeStepCFL>()
{
  InputParameters params = validParams<ElementPostprocessor>();

  // Coupled variables
  params.addRequiredCoupledVar("h", "Water height");
  params.addRequiredCoupledVar("hu", "x-component of the momentum");
  params.addCoupledVar("hv", "y-component of the momentum");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");  
  // Parameter
  params.addParam<Real>("cfl", 0.8, "CFL number to supply by the user");

  return params;
}

TimeStepCFL::TimeStepCFL(const std::string & name, InputParameters parameters) :
    ElementPostprocessor(name, parameters),
    // Coupled variables
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    _hv(_mesh.dimension() == 2 ? coupledValue("hv") : _zero),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos")),
    // Parameters
    _cfl(getParam<Real>("cfl")),
    _value(0.)
{
}

TimeStepCFL::~TimeStepCFL()
{
}

void
TimeStepCFL::initialize()
{
  _value = std::numeric_limits<Real>::max();
}

void
TimeStepCFL::execute()
{
  // Compute cell size
  Real h_cell = std::pow(_current_elem->volume(), 1./_mesh.dimension());

  // Loop over quadrature points
  for (unsigned qp = 0; qp < _qrule->n_points(); ++qp)
  {
    // Compute local max eigenvalue
    RealVectorValue hU(_hu[qp], _hv[qp], 0.);
    Real eigen = hU.size()/_h[qp]+std::sqrt(_eos.c2(_h[qp], hU));

    // Compute the local time step
    _value = std::min(_value, _cfl * h_cell / eigen);
  }
}

Real
TimeStepCFL::getValue()
{
  _communicator.min(_value);
  return _value;
}

void
TimeStepCFL::threadJoin(const UserObject & uo)
{
  const TimeStepCFL & pps = dynamic_cast<const TimeStepCFL &>(uo);
  _value = std::min(_value, pps._value);
}