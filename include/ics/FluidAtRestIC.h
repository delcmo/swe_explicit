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

#ifndef FLUIDATRESTIC_H
#define FLUIDATRESTIC_H

// MOOSE Includes
#include "InitialCondition.h"
#include "Function.h"

// Forward Declarations
class FluidAtRestIC;

template<>
InputParameters validParams<FluidAtRestIC>();

class FluidAtRestIC : public InitialCondition
{
public:

  FluidAtRestIC(const std::string & name,
            InputParameters parameters);

  virtual Real value(const Point & p);

private:
  // Maximum water high
  Real _H;

  // Initial value of the fluid velocity
  Real _vel;

  // Function computing the topology
  Function & _func;  
};

#endif // FLUIDATRESTIC_H
