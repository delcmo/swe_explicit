#include "EntropyViscosityCoefficient.h"

template<>
InputParameters validParams<EntropyViscosityCoefficient>()
{
  InputParameters params = validParams<Material>();

  // Parameters
  params.addParam<bool>("is_first_order", false, "if true, use the first-order viscosity coefficient");
  params.addParam<Real>("Ce", 1., "coefficient for entropy residual");
  params.addParam<Real>("Cjump", 1., "coefficient for jump");
  params.addParam<Real>("Cmax", 0.5, "coefficient for first-order viscosity coefficient");
  // Coupled variables
  params.addRequiredCoupledVar("h", "high/density");
  params.addRequiredCoupledVar("hu", "x component of h*\vec{u}");
  params.addCoupledVar("hv", "y component of h*\vec{u}");
  // Coupled aux variables
  params.addRequiredCoupledVar("entropy", "entropy function");
  params.addRequiredCoupledVar("F", "x-component of the entropy flux ");
  params.addCoupledVar("G", "y-component of the entropy flux ");
  params.addCoupledVar("b", "topology");
  // Coupled variables: jump
  params.addCoupledVar("jump_entropy_flux", "Jump of the of the entropy flux");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");

  return params;
}

EntropyViscosityCoefficient::EntropyViscosityCoefficient(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    // Parameters
    _is_first_order(getParam<bool>("is_first_order")),
    _Ce(getParam<Real>("Ce")),
    _Cjump(getParam<Real>("Cjump")),
    _Cmax(getParam<Real>("Cmax")),
    // Coupled variables
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    _hv(_mesh.dimension() == 2 ? coupledValue("hv") : _zero),
    // Coupled aux variables: entropy
    _E(coupledValue("entropy")),
    _E_old(coupledValueOld("entropy")),
    _E_older(coupledValueOlder("entropy")),
    // Coupled aux variables: entropy flux
    _F_grad(coupledGradient("F")),
    _G_grad(_mesh.dimension() == 2 ? coupledGradient("G") : _grad_zero),
    // Coupled aux variables: topology
    _b(isCoupled("b") ? coupledValue("b") : _zero),
    // Jump of the flux
    _jump(isCoupled("jump_entropy_flux") ? coupledValue("jump_entropy_flux") : _zero),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos")),
    // Materials
    _kappa_old(declarePropertyOld<Real>("kappa")),
    _kappa(declareProperty<Real>("kappa")),
    _kappa_max(declareProperty<Real>("kappa_max")),
    _residual(declareProperty<Real>("residual"))
{
}

EntropyViscosityCoefficient::~EntropyViscosityCoefficient()
{}

void
EntropyViscosityCoefficient::initQpStatefulProperties()
{
  // Cell size
  Real h_cell = std::pow(_current_elem->volume(),1./_mesh.dimension());

  // Set value for the material
  _kappa[_qp] = _Cmax*h_cell;
}

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
  _kappa_max[_qp] = _Cmax*h_cell*(hU.size()/_h[_qp]+std::sqrt(c2));

  // Weights for BDF2
  Real w0 = _t_step > 1 ? (2.*_dt+_dt_old)/(_dt*(_dt+_dt_old)) : 1. / _dt;
  Real w1 = _t_step > 1 ? -(_dt+_dt_old)/(_dt*_dt_old) : -1. / _dt;
  Real w2 = _t_step > 1 ? _dt/(_dt_old*(_dt+_dt_old)) : 0.;

  // Entropy residual
  Real residual = w0*_E[_qp]+w1*_E_old[_qp]+w2*_E_older[_qp];
  residual += _F_grad[_qp](0)+_G_grad[_qp](1);
  residual *= _Ce;
  _residual[_qp] = std::fabs(residual);

  // Froude number
  Real Froude = hU.size()/_h[_qp]/std::sqrt(c2+1.e-6);

  // Normalization parameter
//  Real norm = _eos.gravity()*(_h[_qp]+_b[_qp]+1.e-6);
//  Real norm = _eos.gravity()*std::fabs(_h[_qp]-_b[_qp]+1.e-6);
  Real norm = _eos.gravity()*std::fabs(_h[_qp]+1.e-6);

  // High-order viscosity coefficient
  Real kappa = _t_step == 1 ? _kappa_max[_qp] : h_cell*h_cell*std::fabs(std::max(std::fabs(residual), _Cjump*_jump[_qp]))/norm;

  // Return value of the viscosity coefficient
  _kappa[_qp] = _is_first_order ? _kappa_max[_qp] : std::min(kappa, _kappa_max[_qp]);
}