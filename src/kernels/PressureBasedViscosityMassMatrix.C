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

#include "PressureBasedViscosityMassMatrix.h"

template<>
InputParameters validParams<PressureBasedViscosityMassMatrix>()
{
  InputParameters params = validParams<TimeDerivative>();
  return params;
}

PressureBasedViscosityMassMatrix::PressureBasedViscosityMassMatrix(const std::string & name,
                                             InputParameters parameters) :
    TimeDerivative(name,parameters)
{}

Real
PressureBasedViscosityMassMatrix::computeQpResidual()
{
    return _u[_qp] * _test[_i][_qp];
}

Real
PressureBasedViscosityMassMatrix::computeQpJacobian()
{
    return _test[_j][_qp] * _test[_i][_qp];
}