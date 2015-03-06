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

#ifndef PRESSUREBASEDVISCOSITYLAPLACE_H
#define PRESSUREBASEDVISCOSITYLAPLACE_H

#include "Kernel.h"

// Forward Declarations
class PressureBasedViscosityLaplace;

template<>
InputParameters validParams<PressureBasedViscosityLaplace>();

class PressureBasedViscosityLaplace : public Kernel
{
public:

  PressureBasedViscosityLaplace(const std::string & name,
             InputParameters parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int _jvar);
    
private:
  VariableGradient & _press_grad;
};

#endif // PRESSUREBASEDVISCOSITYLAPLACE_H
