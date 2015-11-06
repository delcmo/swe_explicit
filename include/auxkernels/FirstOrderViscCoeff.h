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

#ifndef FIRSTORDERVISCCOEFF_H
#define FIRSTORDERVISCCOEFF_H

#include "AuxKernel.h"
#include "EquationOfState.h"

class FirstOrderViscCoeff;

template<>
InputParameters validParams<FirstOrderViscCoeff>();

class FirstOrderViscCoeff : public AuxKernel
{
public:

  FirstOrderViscCoeff(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue();

  virtual void compute();

  // Parameters
  Real _Cmax;

  VariableValue & _h;
  VariableValue & _hu;
  VariableValue & _hv;

  // Equation of state
  const EquationOfState & _eos;
};

#endif // FIRSTORDERVISCCOEFF_H
