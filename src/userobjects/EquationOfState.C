#include "EquationOfState.h"
#include "MooseError.h"

template<>
InputParameters validParams<EquationOfState>()
{
  InputParameters params = validParams<UserObject>();
  return params;
}

EquationOfState::EquationOfState(const std::string & name, InputParameters parameters) :
    GeneralUserObject(name, parameters)
{}

EquationOfState::~EquationOfState()
{
  // Destructor, empty
}

Real EquationOfState::pressure(Real, RealVectorValue) const
{
  this->error_not_implemented("pressure");
  return 0.;
}

// The derivative of pressure wrt rho
Real EquationOfState::dp_dh(Real, RealVectorValue) const
{
  this->error_not_implemented("dp_dh");
  return 0.;
}

// The derivative of pressure wrt hu
Real EquationOfState::dp_dhu(Real, RealVectorValue) const
{
  this->error_not_implemented("dp_dhu");
  return 0.;
}

// The derivative of pressure wrt hv
Real EquationOfState::dp_dhv(Real, RealVectorValue) const
{
  this->error_not_implemented("dp_dhv");
  return 0.;
}

// Sound speed square
Real
EquationOfState::c2(Real, RealVectorValue) const
{
  this->error_not_implemented("c2");
  return 0.;
}

void EquationOfState::error_not_implemented(std::string method_name) const
{
  mooseError("Your EquationOfState object does not implement: " + method_name);
}

