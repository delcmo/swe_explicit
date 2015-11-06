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

#ifndef AUXVARIABLESICS_H
#define AUXVARIABLESICS_H

// MOOSE Includes
#include "InitialCondition.h"
#include "EquationOfState.h"

// Forward Declarations
class AuxVariablesICs;

template<>
InputParameters validParams<AuxVariablesICs>();

class AuxVariablesICs : public InitialCondition
{
public:

  AuxVariablesICs(const std::string & name,
            InputParameters parameters);

  virtual Real value(const Point & p);

private:
  // Parameter
  Real _Cmax;
  // Coupled variables
  VariableValue & _h;
  VariableValue & _hu;
  VariableValue & _hv;

  // Equation of state
  const EquationOfState & _eos;
};

#endif // AUXVARIABLESICS_H
