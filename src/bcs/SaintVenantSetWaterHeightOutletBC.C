#include "SaintVenantSetWaterHeightOutletBC.h"
#include "EquationOfState.h"

/** Set the water height at the inlet boundary. This function can only be used with 1-D mesh. 
 This bc function can handle both subsonic and supersonic boundaries. **/

template<>
InputParameters validParams<SaintVenantSetWaterHeightOutletBC>()
{
  InputParameters params = validParams<IntegratedBC>();

  // Equation name:
  params.addParam<std::string>("equ_name", "invalid", "Name of the equation.");
  // Coupled variables
  params.addRequiredCoupledVar("h", "water height");  
  params.addRequiredCoupledVar("hu", "x component of h*vec{u}");
  // Constants and parameters
  params.addRequiredParam<Real>("h_bc", "boundary value of the density/water high h");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "The name of equation of state object to use.");

  return params;
}

SaintVenantSetWaterHeightOutletBC::SaintVenantSetWaterHeightOutletBC(const std::string & name, InputParameters parameters) :
    IntegratedBC(name, parameters),
    // Equation name
    _equ_type("continuity x_mom invalid", getParam<std::string>("equ_name")),
    // Coupled variables
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    // Constants and parameters
    _h_bc(getParam<Real>("h_bc")),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos")),
    // Integer for jacobian terms
    _h_var(coupled("h")),
    _hu_var(coupled("hu"))
{
  // Assert mesh dimension
  if (_mesh.dimension() >= 2)
    mooseError("'" << this->name() << "' can only be used with 1-D mesh since it is designed for the Saint-Venant equations.");
}

Real
SaintVenantSetWaterHeightOutletBC::computeQpResidual()
{
  // Check that the bc is an inlet bc
  Real vel = _hu[_qp]/_h[_qp];
  if (vel*_normals[_qp](0)<0)
    mooseError("'" << this->name() << "' is not/no longer an outlet bc: 'vec{u} dot vec{normal}' is negative");

  // Current bc values of the momentum, sound speed and pressure
  RealVectorValue hU(_hu[_qp], 0., 0.);
  Real c2 = _eos.c2(_h[_qp], hU);
  Real Mach = std::fabs(vel)/std::sqrt(c2);

  // Compute bc pressure and water height
  Real p_bc = _eos.pressure(_h_bc, hU);
  Real h_bc = _h_bc;
  if (Mach>1)
  {
    p_bc = _eos.pressure(_h[_qp], hU);
    h_bc = _h[_qp];
  }

  // Return the value of the bc flux for each equation
  switch (_equ_type)
  {
    case continuity:
      return hU*_normals[_qp]*_test[_i][_qp];
      break;
    case x_mom:
      return (_u[_qp]*_u[_qp]/h_bc+p_bc)*_normals[_qp](0)*_test[_i][_qp];
      break;
    default:
      mooseError("'" << this->name() << "' Invalid equation name.");
  }
}

Real
SaintVenantSetWaterHeightOutletBC::computeQpJacobian()
{
  // Current bc values of the momentum, sound speed and pressure
  RealVectorValue hU(_hu[_qp], 0., 0.);
  Real vel = _hu[_qp]/_h[_qp];  
  Real c2 = _eos.c2(_h[_qp], hU);
  Real Mach = std::fabs(vel)/std::sqrt(c2);
  Real h_bc = _h_bc;
  if (Mach>1)
    h_bc = _h[_qp];

  // Return the value of the bc flux for each equation
  switch (_equ_type)
  {
    case x_mom:
      return _phi[_j][_qp]*(2.*_u[_qp]/h_bc+_eos.dp_dhu(h_bc, hU))*_normals[_qp](0)*_test[_i][_qp];
      break;
    default:
      return 0.;
  }
}

Real
SaintVenantSetWaterHeightOutletBC::computeQpOffDiagJacobian(unsigned jvar)
{
  // Current bc values of the momentum, sound speed and pressure
  RealVectorValue hU(_hu[_qp], 0., 0.);
  Real vel = _hu[_qp]/_h[_qp];
  Real c2 = _eos.c2(_h[_qp], hU);
  Real Mach = std::fabs(vel)/std::sqrt(c2);
  Real h_bc = _h_bc;
  if (Mach>1)
    h_bc = _h[_qp];

  if (jvar == _h_var && Mach>1)
  {
    switch (_equ_type)
    {
      case x_mom:
        return _phi[_j][_qp]*(-_u[_qp]*_u[_qp]/(_h[_qp]*_h[_qp])+_eos.dp_dh(h_bc, hU))*_normals[_qp](0)*_test[_i][_qp];
        break;
      default:
        return 0.;
        break;
    }
  }
  else if (jvar == _hu_var)
  {
    switch (_equ_type)
    {
      case continuity:
        return _phi[_j][_qp]*_normals[_qp](0)*_test[_i][_qp];
        break;
      default:
        return 0.;
        break;
    }
  }
  else
    return 0.;
}

