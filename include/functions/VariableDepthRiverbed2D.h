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

#ifndef VARIABLEDEPTHRIVERBED2D_H
#define VARIABLEDEPTHRIVERBED2D_H

#include "Function.h"

class VariableDepthRiverbed2D;

template<>
InputParameters validParams<VariableDepthRiverbed2D>();

class VariableDepthRiverbed2D : public Function
{
public:
  VariableDepthRiverbed2D(const std::string & name, InputParameters parameters);

  virtual Real value(Real t, const Point & p);

  virtual RealVectorValue gradient(Real t, const Point & p);

protected:
  // x and y-boundaries
  Real _xmin;
  Real _xmax;
  Real _ymin;
  Real _ymax;
};

#endif // VARIABLEDEPTHRIVERBED2D_H
