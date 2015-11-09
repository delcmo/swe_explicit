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

#ifndef LOWORDERVISCCOEFF_H
#define LOWORDERVISCCOEFF_H

#include "AuxKernel.h"
#include "EquationOfState.h"

class LowOrderViscCoeff;

template<>
InputParameters validParams<LowOrderViscCoeff>();

class LowOrderViscCoeff : public AuxKernel
{
public:

  LowOrderViscCoeff(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue() {return 0.;};

  virtual void compute();

  // Parameters
  Real _Cmax;

  // Variables
  VariableValue & _h;
  VariableValue & _hu;
  VariableValue & _hv;

  // Equation of state
  const EquationOfState & _eos;
};

#endif // LOWORDERVISCCOEFF_H
