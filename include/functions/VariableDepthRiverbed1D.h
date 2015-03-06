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

#ifndef VARIABLEDEPTHRIVERBED1D_H
#define VARIABLEDEPTHRIVERBED1D_H

#include "Function.h"

class VariableDepthRiverbed1D;

template<>
InputParameters validParams<VariableDepthRiverbed1D>();

class VariableDepthRiverbed1D : public Function
{
public:
  VariableDepthRiverbed1D(const std::string & name, InputParameters parameters);

  virtual Real value(Real t, const Point & p);

  virtual RealVectorValue gradient(Real t, const Point & p);

protected:
  // x-boundaries
  Real _xmin;
  Real _xmax;
};

#endif // VARIABLEDEPTHRIVERBED1D_H
