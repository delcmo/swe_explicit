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

#ifndef PRESSUREBASEDVISCOSITYMASSMATRIX_H
#define PRESSUREBASEDVISCOSITYMASSMATRIX_H

#include "TimeDerivative.h"
#include "Function.h"

class PressureBasedViscosityMassMatrix;

template<>
InputParameters validParams<PressureBasedViscosityMassMatrix>();

class PressureBasedViscosityMassMatrix : public TimeDerivative
{
public:

  PressureBasedViscosityMassMatrix(const std::string & name,
                        InputParameters parameters);

protected:
    virtual Real computeQpResidual();

    virtual Real computeQpJacobian();

};

#endif // PRESSUREBASEDVISCOSITYMASSMATRIX_H
