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

#include "HighOrderViscCoeff.h"

template<>
InputParameters validParams<HighOrderViscCoeff>()
{
  InputParameters params = validParams<AuxKernel>();

  // Parameters
  params.addParam<Real>("Ce", 1., "coefficient for entropy residual");
  params.addParam<Real>("Cjump", 1., "coefficient for jump");
  // Coupled variables
  params.addRequiredCoupledVar("h", "high/density");
  // Coupled aux variables
  params.addRequiredCoupledVar("entropy", "entropy function");
  params.addRequiredCoupledVar("F", "x-component of the entropy flux ");
  params.addCoupledVar("G", "y-component of the entropy flux ");
  params.addCoupledVar("jump_entropy_flux", "Jump of the of the entropy flux");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");

  return params;
}

HighOrderViscCoeff::HighOrderViscCoeff(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    // Parameters
    _Ce(getParam<Real>("Ce")),
    _Cjump(getParam<Real>("Cjump")),
    // Coupled variables
    _h(coupledValueOld("h")),
    // Coupled aux variables: entropy
    _E(coupledValue("entropy")),
    _E_old(coupledValueOld("entropy")),
    _E_older(coupledValueOlder("entropy")),
    // Coupled aux variables: entropy flux
    _F_grad_old(coupledGradientOld("F")),
    _G_grad_old(_mesh.dimension() == 2 ? coupledGradientOld("G") : _grad_zero),
    _jump(isCoupled("jump_entropy_flux") ? coupledValue("jump_entropy_flux") : _zero),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos"))
{
  mooseAssert(isNodal(), "The variable is nodal and can only be elemental");
}

void
HighOrderViscCoeff::compute()
{
  // Initialize the value storing the first-order visc coeff
  Real ho_visc = 0;

  // Cell size
  Real h_cell = std::pow(_current_elem->volume(),1./_mesh.dimension());

  // Weights for BDF2 temporal integrator
  Real w0 = 1. / _dt;
  Real w1 = -1. / _dt;
//  Real w0 = _t_step > 2 ? (2.*_dt+_dt_old)/(_dt*(_dt+_dt_old)) : 1. / _dt;
//  Real w1 = _t_step > 2 ? -(_dt+_dt_old)/(_dt*_dt_old) : -1. / _dt;
//  Real w2 = _t_step > 2 ? _dt/(_dt_old*(_dt+_dt_old)) : 0.;

  // Loop over the quad pt
  for (unsigned int _qp=0; _qp<_qrule->n_points(); _qp++)
  {
//    std::cout<<"-------------------"<<std::endl;
//    std::cout<<"E="<<_E[_qp]<<" and "<<_E_old[_qp]<<std::endl;
    // Entropy residual
//    Real residual_qp = w0*_E[_qp]+w1*_E_old[_qp]+w2*_E_older[_qp];
    Real residual_qp = w0*_E[_qp]+w1*_E_old[_qp];
    residual_qp += _F_grad_old[_qp](0)+_G_grad_old[_qp](1);
    residual_qp *= _Ce;

    // Add the jump
    residual_qp += _Cjump*_jump[_qp];

    // Compute the norm
    Real norm_qp = _eos.gravity()*(_h[_qp]*_h[_qp]+1.e-6);

    // First-order viscosity coefficient at quad pt
    Real ho_visc_qp = h_cell*h_cell*std::fabs(residual_qp) / norm_qp;
    ho_visc = std::max(ho_visc_qp, ho_visc);
  }

  // Return the piecewise constant value
  _var.setNodalValue(ho_visc);
}