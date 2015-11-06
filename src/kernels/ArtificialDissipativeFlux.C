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

#include "ArtificialDissipativeFlux.h"
/**
This function computes the dissipative terms for all of the equations.
 */
template<>
InputParameters validParams<ArtificialDissipativeFlux>()
{
  InputParameters params = validParams<Kernel>();

  // Coupled aux variables
  params.addCoupledVar("fo_visc_coeff", "first-order viscosity coefficient aux variable");
  // Equation name:
  params.addParam<std::string>("equ_name", "invalid", "Name of the equation.");

  return params;
}

ArtificialDissipativeFlux::ArtificialDissipativeFlux(const std::string & name,
                       InputParameters parameters) :
  Kernel(name, parameters),
    // Coupled aux variables
    _fo_visc(isCoupled("fo_visc_coeff") ? coupledValue("fo_visc_coeff") : _zero),
    // Equation name
    _equ_type("continuity x_mom y_mom invalid", getParam<std::string>("equ_name")),
    // Material
    _kappa(getMaterialProperty<Real>("kappa"))
//    _kappa(_is_implicit ? getMaterialProperty<Real>("kappa") : getMaterialPropertyOld<Real>("kappa"))
{}

Real ArtificialDissipativeFlux::computeQpResidual()
{
//  Real kappa = _kappa[_qp];
  Real kappa = _fo_visc[_qp];

//  std::cout<<"=========================="<<std::endl;
//  std::cout<<_qp<<std::endl;
//  std::cout<<_current_elem[0]<<std::endl;
//  std::cout.precision(10);
//  std::cout<<"kappa="<<kappa<<" and grad_u="<<_grad_u[_qp](0)<<std::endl;

  switch (_equ_type)
  {
  case continuity:
//    std::cout<<"cont="<<kappa*_grad_u[_qp](0)<<std::endl;
    return kappa*_grad_u[_qp]*_grad_test[_i][_qp];
    break;
  case x_mom:
//    std::cout<<"mom="<<kappa*_grad_u[_qp](0)<<std::endl;
    return kappa*_grad_u[_qp]*_grad_test[_i][_qp];
    break;
  case y_mom:
    return kappa*_grad_u[_qp]*_grad_test[_i][_qp];
    break;
  default:
    mooseError("Invalid equation name.");
  }
}

Real ArtificialDissipativeFlux::computeQpJacobian()
{
  return 0.;
}

Real ArtificialDissipativeFlux::computeQpOffDiagJacobian( unsigned int _jvar)
{
  return 0.;
}
