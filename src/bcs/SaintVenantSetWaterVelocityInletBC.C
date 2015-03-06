#include "SaintVenantSetWaterVelocityInletBC.h"
#include "EquationOfState.h"

/** Set the fluid velocity at the boundary **/

template<>
InputParameters validParams<SaintVenantSetWaterVelocityInletBC>()
{
  InputParameters params = validParams<IntegratedBC>();

  // Equation name:
  params.addParam<std::string>("equ_name", "invalid", "Name of the equation.");
  // Coupled variables
  params.addRequiredCoupledVar("h", "water height");
  params.addRequiredCoupledVar("hu", "x-mom of h*vec{u}");  
  // Constants and parameters
  params.addRequiredParam<Real>("u_bc", "boundary value of the value");
  params.addParam<Real>("h_bc", "boundary value of the water height (only used if fluid becomes supersonic at the inlet.");  
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "The name of equation of state object to use.");

  return params;
}


SaintVenantSetWaterVelocityInletBC::SaintVenantSetWaterVelocityInletBC(const std::string & name, InputParameters parameters) :
    IntegratedBC(name, parameters),
    // Equation name
    _equ_type("continuity x_mom invalid", getParam<std::string>("equ_name")),
    // Coupled variables
    _h(coupledValue("h")),
    // Constants and parameters
    _u_bc(getParam<Real>("u_bc")),
    _h_bc(isCoupled("h_bc") ? getParam<Real>("h_bc") : 0.),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos")),
    // Integer for jacobian terms
    _h_var(coupled("h")),
    _hu_var(coupled("hu"))
{
  // Assert mesh dimension
  if (_mesh.dimension() > 1)
    mooseError("'" << this->name() << "' can only be used with 1-D mesh since it is designed for the Saint-Venant equations.");
  // Determine whether or not u_bc is specified in the input file
  _h_bc_specified = isCoupled("h_bc") ? true : false;
}

Real
SaintVenantSetWaterVelocityInletBC::computeQpResidual()
{
  // Check that the bc is an inlet bc
  if (_u_bc*_normals[_qp](0)>0)
    mooseError("'" << this->name() << "' is not/no longer an inlet bc: 'vec{u} dot vec{normal}' is greater than zero");

  // Current bc values of the momentum, sound speed and pressure
  RealVectorValue hU(_h[_qp]*_u_bc, 0., 0.);
  Real c2 = _eos.c2(_h[_qp], hU);
  Real Mach = std::fabs(_u_bc)/std::sqrt(c2);
  Real p_bc = _eos.pressure(_h[_qp], hU);
  Real h_bc = _h[_qp];

  // If the fluid is supersonic u_bc is used to evaluate hU at the boundary
  if (Mach>1)
  {
    if (!_h_bc_specified)
      mooseError("'" << this->name() << "': the fluid becomes supersonic but you did not sepcify an inlet water height value in the input file.");
    hU(0) = _h_bc*_u_bc;
    p_bc = _eos.pressure(_h_bc, hU);
    h_bc = _h_bc;
  }

  // Return flux
  switch (_equ_type)
  {
    case continuity:
      return h_bc*_u_bc*_normals[_qp](0)*_test[_i][_qp];
      break;
    case x_mom:
      return (_u_bc*_u_bc*h_bc+p_bc)*_normals[_qp](0)*_test[_i][_qp];
      break;
    default:
      mooseError("'" << this->name() << "' Invalid equation name.");
  }
}

Real
SaintVenantSetWaterVelocityInletBC::computeQpJacobian()
{
  return 0.;
}

Real
SaintVenantSetWaterVelocityInletBC::computeQpOffDiagJacobian(unsigned jvar)
{
  return 0.;
}

