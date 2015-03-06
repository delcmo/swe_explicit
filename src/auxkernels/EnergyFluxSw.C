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
#include "EnergyFluxSw.h"

template<>
InputParameters validParams<EnergyFluxSw>()
{
  InputParameters params = validParams<AuxKernel>();

  // Momentum component
  params.addRequiredCoupledVar("momentum", "momentum component");
  // Coupled variables
  params.addRequiredCoupledVar("h", "water height");
  params.addRequiredCoupledVar("hu", "x component of h*vec{u}");
  params.addCoupledVar("hv", "y component of h*vec{u}");
  // Coupled aux variables
  params.addCoupledVar("b", "topology");
  // Gravity
  params.addParam<Real>("gravity", 9.81, "value of the gravity");

  return params;
}

EnergyFluxSw::EnergyFluxSw(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    // Momentum component
    _mom(coupledValue("momentum")),
    // Coupled variables
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    _hv(_mesh.dimension() == 2 ? coupledValue("hv") : _zero),
    // Coupled aux variables
    _b(isCoupled("b") ? coupledValue("b") : _zero),
    // Gravity:
    _g(getParam<Real>("gravity"))
{}

Real
EnergyFluxSw::computeValue()
{
  RealVectorValue U(_hu[_qp]/_h[_qp], _hv[_qp]/_h[_qp], 0.);
  return _mom[_qp]*(_g*(_h[_qp]+_b[_qp])+0.5*U.size_sq());
}
