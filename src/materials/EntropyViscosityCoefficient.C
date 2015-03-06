#include "EntropyViscosityCoefficient.h"

template<>
InputParameters validParams<EntropyViscosityCoefficient>()
{
  InputParameters params = validParams<Material>();

  // Parameters
  params.addParam<bool>("is_first_order", false, "if true, use the first-order viscosity coefficient");
  params.addParam<Real>("Ce", 1., "coefficient for high-order viscosity coefficient");
  params.addParam<Real>("gravity", 9.81, "gravity");
  // Coupled variables
  params.addRequiredCoupledVar("h", "high/density");
  params.addRequiredCoupledVar("hu", "x component of h*\vec{u}");
  params.addCoupledVar("hv", "y component of h*\vec{u}");
  // Coupled aux variables
  params.addRequiredCoupledVar("entropy", "entropy function");
  params.addRequiredCoupledVar("F", "x-component of the entropy flux ");
  params.addCoupledVar("G", "y-component of the entropy flux ");
  params.addCoupledVar("b", "topology");  
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");

  return params;
}

EntropyViscosityCoefficient::EntropyViscosityCoefficient(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    // Parameters
    _is_first_order(getParam<bool>("is_first_order")),
    _Ce(getParam<Real>("Ce")),
    _g(getParam<Real>("gravity")),
    // Coupled variables
    _h(coupledValueOld("h")),
    _hu(coupledValueOld("hu")),
    _hv(_mesh.dimension() == 2 ? coupledValueOld("hv") : _zero),
    // Coupled aux variables: entropy
    _E(coupledValue("entropy")),
    _E_old(coupledValueOld("entropy")),
    _E_older(coupledValueOlder("entropy")),
    // Coupled aux variables: entropy flux
    _F_grad(coupledGradientOld("F")),
    _G_grad(_mesh.dimension() == 2 ? coupledGradientOld("G") : _grad_zero),
    // Coupled aux variables: topology
    _b(isCoupled("b") ? coupledValue("b") : _zero),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos")),
    // Materials
    _kappa(declareProperty<Real>("kappa")),
    _kappa_max(declareProperty<Real>("kappa_max")),
    _residual(declareProperty<Real>("residual"))
{
}

EntropyViscosityCoefficient::~EntropyViscosityCoefficient()
{}

void
EntropyViscosityCoefficient::computeQpProperties()
{
  // Cell size
  Real h_cell = std::pow(_current_elem->volume(),1./_mesh.dimension());
  
  // Momentum vector
  RealVectorValue hU(_hu[_qp], _hv[_qp], 0.);

  // Speed of sound
  Real c2 = _eos.c2(_h[_qp], hU);

  // First-order viscosity coefficient
  _kappa_max[_qp] = 0.5*h_cell*(hU.size()/_h[_qp]+std::sqrt(c2));

  // Entropy residual
  Real residual = (_E_old[_qp]+_E_older[_qp])/_dt;
  residual += _F_grad[_qp](0)+_G_grad[_qp](1);
  _residual[_qp] = std::fabs(residual);

  // Froude number
  Real Froude = hU.size()/_h[_qp]/std::sqrt(_g*(_h[_qp]+1.e-6));
  
  // Normalization parameter
  Real norm = _g*(_h[_qp]+_b[_qp]+1.e-6);

  // High-order viscosity coefficient
  Real kappa = _t_step == 1 ? _kappa_max[_qp] : _Ce*h_cell*h_cell*std::fabs(residual/norm);

  // Return value of the viscosity coefficient
  _kappa[_qp] = _is_first_order ? _kappa_max[_qp] : std::min(kappa, _kappa_max[_qp]);
}