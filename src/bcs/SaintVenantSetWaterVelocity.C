#include "SaintVenantSetWaterVelocity.h"
#include "EquationOfState.h"

/** Set the fluid velocity at the boundary **/

template<>
InputParameters validParams<SaintVenantSetWaterVelocity>()
{
  InputParameters params = validParams<IntegratedBC>();

  // Equation name:
  params.addParam<std::string>("equ_name", "invalid", "Name of the equation.");
  // Coupled variables
  params.addRequiredCoupledVar("h", "water height");
  params.addRequiredCoupledVar("hu", "x-mom of h*vec{u}");  
  // Constants and parameters
  params.addRequiredParam<Real>("u_bc", "boundary value of the value");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "The name of equation of state object to use.");

  return params;
}


SaintVenantSetWaterVelocity::SaintVenantSetWaterVelocity(const std::string & name, InputParameters parameters) :
    IntegratedBC(name, parameters),
    // Equation name
    _equ_type("continuity x_mom invalid", getParam<std::string>("equ_name")),
    // Coupled variables
    _h(coupledValue("h")),
    // Constants and parameters
    _u_bc(getParam<Real>("u_bc")),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos")),
    // Integer for jacobian terms
    _h_var(coupled("h")),
    _hu_var(coupled("hu"))
{
  if (_mesh.dimension() > 1)
    mooseError("'" << this->name() << "' can only be used with 1-D mesh since it is deisnged for the Saint-Venant equations.");
}

Real
SaintVenantSetWaterVelocity::computeQpResidual()
{
  RealVectorValue hU(_h[_qp]*_u_bc, 0., 0.);
  Real p = _eos.pressure(_h[_qp], hU);
  switch (_equ_type)
  {
    case continuity:
      return _h[_qp]*_u_bc*_normals[_qp](0)*_test[_i][_qp];
      break;
    case x_mom:
      return (_u_bc*_u_bc*_h[_qp]+p)*_normals[_qp](0)*_test[_i][_qp];
      break;
    default:
      mooseError("'" << this->name() << "' Invalid equation name.");
  }
}

Real
SaintVenantSetWaterVelocity::computeQpJacobian()
{
  return 0.;
}

Real
SaintVenantSetWaterVelocity::computeQpOffDiagJacobian(unsigned jvar)
{
  return 0.;
}
