/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
/**
This function computes the energy of the fluid.
**/
#include "EnergySw.h"

template<>
InputParameters validParams<EnergySw>()
{
  InputParameters params = validParams<AuxKernel>();
  
  // Coupled variables
  params.addRequiredCoupledVar("h", "water height");
  params.addRequiredCoupledVar("hu", "x component of h*vec{u}");
  params.addCoupledVar("hv", "y component of h*vec{u}");
  // Gravity
  params.addParam<Real>("gravity", 9.81, "value of the gravity");

  return params;
}

EnergySw::EnergySw(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    // Coupled variables
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    _hv(_mesh.dimension() == 2 ? coupledValue("hv") : _zero),
    // Gravity:
    _g(getParam<Real>("gravity"))
{}

Real
EnergySw::computeValue()
{
  RealVectorValue U(_hu[_qp]/_h[_qp], _hv[_qp]/_h[_qp], 0.);
  return 0.5*_h[_qp]*(_g*_h[_qp]+U.size_sq());
}
