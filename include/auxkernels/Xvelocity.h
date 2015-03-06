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

#ifndef XVELOCITY_H
#define XVELOCITY_H

#include "AuxKernel.h"

class Xvelocity;

template<>
InputParameters validParams<Xvelocity>();

class Xvelocity : public AuxKernel
{
public:

  Xvelocity(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue();

  VariableValue & _h;
  VariableValue & _hu;
};

#endif //XVELOCITY_H
