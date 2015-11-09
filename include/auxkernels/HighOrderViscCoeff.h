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

#ifndef HIGHORDERVISCCOEFF_H
#define HIGHORDERVISCCOEFF_H

#include "AuxKernel.h"
#include "EquationOfState.h"

class HighOrderViscCoeff;

template<>
InputParameters validParams<HighOrderViscCoeff>();

class HighOrderViscCoeff : public AuxKernel
{
public:

  HighOrderViscCoeff(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue() {return 0.;};

  virtual void compute();

  // Parameters
  Real _Ce;
  Real _Cjump;

  // Variables
  VariableValue & _h;

  // Coupled aux variables: entropy
  VariableValue & _E;
  VariableValue & _E_old;
  VariableValue & _E_older;

  // Coupled aux variables: entropy flux
  VariableGradient & _F_grad_old;
  VariableGradient & _G_grad_old;
  VariableValue & _jump;

  // Equation of state
  const EquationOfState & _eos;
};

#endif // HIGHORDERVISCCOEFF_H
