#include "WaterHeightEqu.h"

/** Compute the advection term of the continuity/water height Shallow-water equations **/

template<>
InputParameters validParams<WaterHeightEqu>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("hu", "x component of h*vec{u}");
  params.addCoupledVar("hv", "y component of h*vec{u}");

  return params;
}

WaterHeightEqu::WaterHeightEqu(const std::string & name, InputParameters parameters)
  :Kernel(name, parameters),
    _hu(coupledValue("hu")),
    _hv(_mesh.dimension() == 2 ? coupledValue("hv") : _zero),
    _hu_var(coupled("hu")),
    _hv_var(_mesh.dimension() == 2 ? coupled("hv") : 0)
{}

Real
WaterHeightEqu::computeQpResidual()
{
  RealVectorValue conv(_hu[_qp], _hv[_qp], 0.);

  // return
  return -conv*_grad_test[_i][_qp];
}

Real
WaterHeightEqu::computeQpJacobian()
{
  return 0.;
}

Real
WaterHeightEqu::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar==_hu_var)
  {
    return -_phi[_j][_qp]*_grad_test[_i][_qp](0);
  }
  else if (jvar==_hv_var)
  {
    return -_phi[_j][_qp]*_grad_test[_i][_qp](1);
  }
  else
    return 0.;
}