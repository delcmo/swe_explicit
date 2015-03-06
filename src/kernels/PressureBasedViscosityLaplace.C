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

#include "PressureBasedViscosityLaplace.h"

/** This function computes the Laplace operator of the pressure **/

template<>
InputParameters validParams<PressureBasedViscosityLaplace>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("pressure", "pressure variable");

  return params;
}

PressureBasedViscosityLaplace::PressureBasedViscosityLaplace(const std::string & name,
                       InputParameters parameters) :
  Kernel(name, parameters),
    _press_grad(coupledGradient("pressure"))
{}

Real PressureBasedViscosityLaplace::computeQpResidual()
{
  return _press_grad[_qp]*_grad_test[_i][_qp];
}

Real PressureBasedViscosityLaplace::computeQpJacobian()
{
  return _grad_phi[_j][_qp]*_grad_test[_i][_qp];
}

Real PressureBasedViscosityLaplace::computeQpOffDiagJacobian( unsigned int _jvar)
{
  return 0.;
}