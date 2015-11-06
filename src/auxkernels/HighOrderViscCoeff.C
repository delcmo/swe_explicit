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
This function computes the density of the fluid.
**/
#include "HighOrderViscCoeff.h"

template<>
InputParameters validParams<HighOrderViscCoeff>()
{
  InputParameters params = validParams<AuxKernel>();

  // Parameters
  params.addParam<Real>("Cmax", 0.5, "coefficient for first-order viscosity coefficient");
  // Coupled variables
  params.addRequiredCoupledVar("h", "water height");
  params.addRequiredCoupledVar("hu", "x component of h*vec{u}");
  params.addCoupledVar("hv", "y component of h*\vec{u}");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");

  return params;
}

HighOrderViscCoeff::HighOrderViscCoeff(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    // Parameters
    _Cmax(getParam<Real>("Cmax")),
    // Coupled variables
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    _hv(_mesh.dimension() == 2 ? coupledValue("hv") : _zero),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos"))
{
  mooseAssert(isNodal(), "The variable is nodal and can only be elemental");
}

//Real
//HighOrderViscCoeff::computeValue()
//{
//  // Cell size
//  Real h_cell = std::pow(_current_elem->volume(),1./_mesh.dimension());
//
//  // Momentum vector
//  RealVectorValue hU(_hu[_qp], _hv[_qp], 0.);
//
//  // Speed of sound
//  Real c2 = _eos.c2(_h[_qp], hU);
//
//  // First-order viscosity coefficient
//  return _Cmax*h_cell*(hU.size()/_h[_qp]+std::sqrt(c2));
//}

void
HighOrderViscCoeff::compute()
{
  Real fo_visc = 0;
  for (unsigned int _qp=0; _qp<_qrule->n_points(); _qp++)
  {
    // Cell size
    Real h_cell = std::pow(_current_elem->volume(),1./_mesh.dimension());

    // Momentum vector
    RealVectorValue hU(_hu[_qp], _hv[_qp], 0.);

    // Speed of sound
    Real c2 = _eos.c2(_h[_qp], hU);

    // First-order viscosity coefficient
    Real fo_visc_qp = _Cmax*h_cell*(hU.size()/_h[_qp]+std::sqrt(c2));
    fo_visc = std::max(fo_visc_qp, fo_visc);
  }

  // Return the value
  _var.setNodalValue(fo_visc);
}