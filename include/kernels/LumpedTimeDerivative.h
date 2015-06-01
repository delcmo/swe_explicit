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

#ifndef LUMPEDTIMEDERIVATIVE_H
#define LUMPEDTIMEDERIVATIVE_H

#include "TimeKernel.h"
#include "MooseVariableInterface.h"

// Forward Declaration
class LumpedTimeDerivative;

template<>
InputParameters validParams<LumpedTimeDerivative>();

class LumpedTimeDerivative : public TimeKernel
{
public:
  LumpedTimeDerivative(const std::string & name, InputParameters parameters);

  virtual void computeResidual();
  virtual void computeJacobian();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  // Nodal values
  VariableValue & _u_nodal;
  VariableValue & _u_old_nodal;
};

#endif //LUMPEDTIMEDERIVATIVE_H
