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
    _h(coupledValueOld("h")),
    _hu(coupledValueOld("hu")),
    _hv(_mesh.dimension() == 2 ? coupledValueOld("hv") : _zero),
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
  return 0.;
}

Real
MomentumEqu::computeQpOffDiagJacobian(unsigned int jvar)
{
  return 0.;
}