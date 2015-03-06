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

#ifndef ENERGYFLUXSW_H
#define ENERGYFLUXSW_H

#include "AuxKernel.h"

class EnergyFluxSw;

template<>
InputParameters validParams<EnergyFluxSw>();

class EnergyFluxSw : public AuxKernel
{
public:

  EnergyFluxSw(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue();

  // Momentum comoponent
  VariableValue & _mom;

  // Coupled variables
  VariableValue & _h;
  VariableValue & _hu;
  VariableValue & _hv;

  // Coupled aux variables
  VariableValue & _b;

  // Gravity
  Real _g;
};

#endif //ENERGYFLUXSW_H
