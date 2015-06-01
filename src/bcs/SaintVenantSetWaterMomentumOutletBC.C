#include "SaintVenantSetWaterMomentumOutletBC.h"
#include "EquationOfState.h"

/** Set the fluid velocity at the boundary **/

template<>
InputParameters validParams<SaintVenantSetWaterMomentumOutletBC>()
{
  InputParameters params = validParams<IntegratedBC>();

  // Equation name:
  params.addParam<std::string>("equ_name", "invalid", "Name of the equation.");
  // Coupled variables
  params.addRequiredCoupledVar("h", "water height");
  params.addRequiredCoupledVar("hu", "x-mom of h*vec{u}");  
  // Constants and parameters
  params.addRequiredParam<Real>("hu_bc", "boundary value of the water momentum.");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "The name of equation of state object to use.");

  return params;
}


SaintVenantSetWaterMomentumOutletBC::SaintVenantSetWaterMomentumOutletBC(const std::string & name, InputParameters parameters) :
    IntegratedBC(name, parameters),
    // Equation name
    _equ_type("continuity x_mom invalid", getParam<std::string>("equ_name")),
    // Coupled variables
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    // Constants and parameters
    _hu_bc(getParam<Real>("hu_bc")),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos")),
    // Integer for jacobian terms
    _h_var(coupled("h")),
    _hu_var(coupled("hu"))
{
  // Assert mesh dimension
  mooseAssert(_mesh.dimension() > 1, "'" << this->name() << "' can only be used with 1-D mesh since it is designed for the Saint-Venant equations.");
}

Real
SaintVenantSetWaterMomentumOutletBC::computeQpResidual()
{
  // Check that the bc is an inlet bc
  mooseAssert(_hu[_qp]/_h[_qp]*_normals[_qp](0)>0, "'" << this->name() << "' is not/no longer an inlet bc: 'vec{u} dot vec{normal}' is greater than zero");

  // Current bc values of the momentum, sound speed
  RealVectorValue hU_bc(_hu_bc, 0., 0.);
  Real c2 = _eos.c2(_h[_qp], hU_bc);
  Real Fr = std::fabs(_hu_bc/_h[_qp])/std::sqrt(c2);
  Real h_bc = _h[_qp];

  // If the fluid is supersonic u_bc and h_bc are used to compute hU at the boundary
  if (Fr>1)
  {
    hU_bc(0) = _hu[_qp];
  }

  // Compute the pressure
  Real p_bc = _eos.pressure(h_bc, hU_bc);

  // Return flux
  switch (_equ_type)
  {
    case continuity:
      return _hu_bc*_normals[_qp](0)*_test[_i][_qp];
      break;
    case x_mom:
      return (_hu_bc*_hu_bc/h_bc+p_bc)*_normals[_qp](0)*_test[_i][_qp];
      break;
    default:
      mooseError("'" << this->name() << "' Invalid equation name.");
  }
}

Real
SaintVenantSetWaterMomentumOutletBC::computeQpJacobian()
{
  return 0.;
}

Real
SaintVenantSetWaterMomentumOutletBC::computeQpOffDiagJacobian(unsigned jvar)
{
  return 0.;
}

