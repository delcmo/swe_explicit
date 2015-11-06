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

#include "AuxVariablesICs.h"

template<>
InputParameters validParams<AuxVariablesICs>()
{
  InputParameters params = validParams<InitialCondition>();
  // Parameters
  params.addParam<Real>("Cmax", 0.5, "coefficient for first-order viscosity coefficient");
  // Coupled variables
  params.addRequiredCoupledVar("h", "water height");
  params.addRequiredCoupledVar("hu", "x component of h*vec{u}");
  params.addCoupledVar("hv", 0., "y component of h*vec{u}");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");
  return params;
}

AuxVariablesICs::AuxVariablesICs(const std::string & name,
                     InputParameters parameters) :
    InitialCondition(name, parameters),
    // Parameters
    _Cmax(getParam<Real>("Cmax")),
    // Coupled variables
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    _hv(coupledValue("hv")),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos"))
{}

Real
AuxVariablesICs::value(const Point & p)
{
  // Cell size
//  Real h_cell = std::pow(_current_elem->volume(),1./_mesh.dimension());
  Real h_cell = _current_elem->volume();

  // Momentum vector
  RealVectorValue hU(_hu[_qp], _hv[_qp], 0.);

  // Speed of sound
  Real c2 = _eos.c2(_h[_qp], hU);

  // First-order viscosity coefficient
  return _Cmax*h_cell*(hU.size()/_h[_qp]+std::sqrt(c2));
}
