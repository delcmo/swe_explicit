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

#ifndef ICSWITHTOPOLOGY1D_H
#define ICSWITHTOPOLOGY1D_H

// MOOSE Includes
#include "InitialCondition.h"
#include "Function.h"

// Forward Declarations
class IcsWithTopology1D;

template<>
InputParameters validParams<IcsWithTopology1D>();

class IcsWithTopology1D : public InitialCondition
{
public:

  IcsWithTopology1D(const std::string & name,
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

#endif // ICSWITHTOPOLOGY1D_H
