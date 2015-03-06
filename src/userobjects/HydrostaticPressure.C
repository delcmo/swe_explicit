#include "HydrostaticPressure.h"

template<>
InputParameters validParams<HydrostaticPressure>()
{
  InputParameters params = validParams<EquationOfState>();
  params.addParam<Real>("gravity", 9.81, "value of the gravity");

  return params;
}

HydrostaticPressure::HydrostaticPressure(const std::string & name, InputParameters parameters) :
    EquationOfState(name, parameters),
    _g(getParam<Real>("gravity"))
{}

HydrostaticPressure::~HydrostaticPressure()
{
  // Destructor, empty
}

Real HydrostaticPressure::pressure(Real h, RealVectorValue hU) const
{
  return 0.5*_g*h*h;
}

// The derivative of pressure wrt h
Real HydrostaticPressure::dp_dh(Real h, RealVectorValue hU) const
{
  return _g*h;
}

// The derivative of pressure wrt hu
Real HydrostaticPressure::dp_dhu(Real h, RealVectorValue hU) const
{
  return 0.;
}

// The derivative of pressure wrt hv
Real HydrostaticPressure::dp_dhv(Real h, RealVectorValue hU) const
{
  return 0.;
}

// Sound speed square
Real
HydrostaticPressure::c2(Real h, RealVectorValue hU) const
{
  return _g*h;
}