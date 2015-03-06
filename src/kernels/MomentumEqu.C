#include "MomentumEqu.h"

/** Compute the advection term of the momentum Shallow-Water equations. The pressure P is computed from the material class EquationOfState. The topography is given as a function. The momentum vector is denoted by hU=(hu, hv) and the water height is 'h'. **/

template<>
InputParameters validParams<MomentumEqu>()
{
  InputParameters params = validParams<Kernel>();

  // Coupled variables
  params.addRequiredCoupledVar("h", "water height");
  params.addRequiredCoupledVar("hu", "x component of h*vec{u}");
  params.addCoupledVar("hv", "y component of h*vec{u}");
  // Coupled aux variables
  params.addCoupledVar("b", "topology");
  // Constants and parameters
  params.addRequiredParam<Real>("gravity", "gravity");
  params.addRequiredParam<unsigned int>("component", "number of component (0 = x, 1 = y)");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");

  return params;
}

MomentumEqu::MomentumEqu(const std::string & name, InputParameters parameters)
  :Kernel(name, parameters),
    // Coupled variables
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    _hv(_mesh.dimension() == 2 ? coupledValue("hv") : _zero),
    // Coupled aux variables
    _b_grad(isCoupled("b") ? coupledGradient("b") : _grad_zero),
    // Constants and parameters
    _g(getParam<Real>("gravity")),
    _component(getParam<unsigned int>("component")),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos")),
    // Integer for jacobian terms
    _h_var(coupled("h")),
    _hu_var(coupled("hu")),
    _hv_var(_mesh.dimension() == 2 ? coupled("hv") : 0)
{}

Real
MomentumEqu::computeQpResidual()
{
  // Pressure
  RealVectorValue hU(_hu[_qp], _hv[_qp], 0.);  
  Real p = _eos.pressure(_h[_qp], hU)*_grad_test[_i][_qp](_component);

  // Advection
  Real advc = _u[_qp]/_h[_qp]*(hU*_grad_test[_i][_qp]);

  // Topology
  Real tplg_grad = _g*_h[_qp]*_b_grad[_qp](_component)*_test[_i][_qp];

  // return value
  return -advc-p+tplg_grad;
}

Real
MomentumEqu::computeQpJacobian()
{
  // Pressure
  RealVectorValue hU(_hu[_qp], _hv[_qp], 0.);
  Real dpdu = _phi[_j][_qp]*_grad_test[_i][_qp](_component);
  if (_component == 0)
    dpdu *= _eos.dp_dhu(_h[_qp], hU);
  else if (_component == 1)
    dpdu *= _eos.dp_dhv(_h[_qp], hU);
  else
    mooseError("'" << this->name() << "' can only be used with 1 and 2-D mesh.");

  // Advection
  hU(_component) *= 2.;
  Real dadvcdu = _phi[_j][_qp]/_h[_qp]*(hU*_grad_test[_i][_qp]);

  // Topology
  Real dtplg_grad_du= 0.;

  // return value
  return -dadvcdu-dpdu+dtplg_grad_du;
}

Real
MomentumEqu::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _h_var) // water height 'h'
  {
    RealVectorValue hU(_hu[_qp], _hv[_qp], 0.);    
    // Pressure
    Real dpdh = _phi[_j][_qp]*_grad_test[_i][_qp](_component);
    dpdh *= _eos.dp_dh(_h[_qp], hU);

    // Advection
    Real dadvcdh = -_u[_qp]/(_h[_qp]*_h[_qp])*(hU*_grad_test[_i][_qp]);
    dadvcdh *= _phi[_j][_qp];

    // Topology
    Real dtplg_grad_dh = _phi[_j][_qp]*_g*_b_grad[_qp](_component)*_test[_i][_qp];

    // return value
    return -dadvcdh-dpdh+dtplg_grad_dh;
  }
  else if (jvar == _hu_var && _component == 1) // x-component of momentum vector 'hu'
  {
    RealVectorValue hU(_hu[_qp], _hv[_qp], 0.);
    // Pressure
    Real dpdhu = _phi[_j][_qp]*_grad_test[_i][_qp](_component);
    dpdhu *= _eos.dp_dhu(_h[_qp], hU);

    // Advection
    hU(0) = 1.;
    hU(1) = 0.;
    Real dadvcdhu = _u[_qp]/_h[_qp]*(hU*_grad_test[_i][_qp]);
    dadvcdhu *= _phi[_j][_qp];

    // Topology
    Real dtplg_grad_dhu=0.;

    // return value
    return -dadvcdhu-dpdhu+dtplg_grad_dhu;
  }
  else if (jvar == _hv_var && _component == 0) // y-component of momentum vector 'hv'
  {
    RealVectorValue hU(_hu[_qp], _hv[_qp], 0.);    
    // Pressure
    Real dpdhv = _phi[_j][_qp]*_grad_test[_i][_qp](_component);
    dpdhv *= _eos.dp_dhv(_h[_qp], hU);

    // Advection
    hU(0) = 0.;
    hU(1) = 1.;
    Real dadvcdhv = _u[_qp]/_h[_qp]*(hU*_grad_test[_i][_qp]);
    dadvcdhv *= _phi[_j][_qp];

    // Topology
    Real dtplg_grad_dhv=0.;

    // return value
    return -dadvcdhv-dpdhv+dtplg_grad_dhv;
  }
  else
    return 0.;
    
}