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

#include "IcsWithTopology1D.h"

template<>
InputParameters validParams<IcsWithTopology1D>()
{
  InputParameters params = validParams<InitialCondition>();

  // Initial conditions:
  params.addRequiredParam<Real>("H", "Maximum water heigh i.e. when the topology b=0");
  params.addRequiredParam<Real>("u", "Initial value of the fluid velocity");  
  // Function for topology
  params.addRequiredParam<FunctionName>("topology", "function computing the topology.");

  return params;
}

IcsWithTopology1D::IcsWithTopology1D(const std::string & name,
                     InputParameters parameters) :
    InitialCondition(name, parameters),
    // IC parameters
    _H(getParam<Real>("H")),
    _vel(getParam<Real>("u")),
    // Function for topology
    _func(getFunction("topology"))
{}

Real
IcsWithTopology1D::value(const Point & p)
{
  // Compute the water height 'h'
  Real h(0.);
  if (_H - _func.value(_t, p)<0)
    mooseError("Negative water height initial values computed in "<<name()<<".");
  else
    h = _H - _func.value(_t, p);

  // Return values for ics
  if (_var.name() == "h")
    return h;
  else if (_var.name() == "hu")
    return h*_vel;
  else
    mooseError("The variable "<<_var.name()<<" cannot be initialized in "<<name()<<". The variable names must be taken among 'h' and 'hu'");
}
