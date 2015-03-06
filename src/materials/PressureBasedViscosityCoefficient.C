#include "PressureBasedViscosityCoefficient.h"

template<>
InputParameters validParams<PressureBasedViscosityCoefficient>()
{
  InputParameters params = validParams<Material>();

  // Pressure-based viscosity type
  params.addParam<std::string>("pressure_based_visc_type", "JST", "Name of the pressure-based viscosity to use.");
  // Coupled variable
  params.addRequiredCoupledVar("h", "high/density");
  params.addRequiredCoupledVar("hu", "x component of h*vec{u}");
  params.addCoupledVar("hv", "y component of h*vec{u}");  
  params.addRequiredCoupledVar("press_laplace", "variable computing the laplace of pressure");
  // Coupled aux variable
  params.addRequiredCoupledVar("pressure", "pressure");
  params.addRequiredCoupledVar("norm_velocity", "norm of the velocity");  
  // Pressure based parameter
  params.addParam<Real>("Ce", 1., "Constant that multiplies the viscosity coefficient");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");

  return params;
}

PressureBasedViscosityCoefficient::PressureBasedViscosityCoefficient(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    // Pressure-based viscosity type
    _pbv_type("JST HMP ST INVALID", getParam<std::string>("pressure_based_visc_type")),
    // Coupled variable
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    _hv(_mesh.dimension() == 2 ? coupledValue("hv") : _zero),
    _press_laplace(coupledValue("press_laplace")),
    // Coupled aux variable
    _press(coupledValue("pressure")),
    _press_grad(coupledGradient("pressure")),
    _norm_vel(coupledValue("norm_velocity")),
    // Lapidus parameter
    _Ce(getParam<Real>("Ce")),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos")),
    // Materials
    _kappa(declareProperty<Real>("kappa")),
    _kappa_max(declareProperty<Real>("kappa_max"))
{}

PressureBasedViscosityCoefficient::~PressureBasedViscosityCoefficient()
{
}

void
PressureBasedViscosityCoefficient::computeQpProperties()
{
  // Cell size
  Real h_cell = _current_elem->hmin();

  // Speed of sound
  RealVectorValue hU(_hu[_qp], 0., 0.);
  Real c2=_eos.c2(_h[_qp], hU);

  // Compute normalization parameter
  Real eps = std::sqrt(std::numeric_limits<Real>::min());
  Real norm = 0.;
  switch (_pbv_type)
  {
    case JST:
      norm = std::fabs(_press[_qp]);
      break;
    case HMP:
      norm = h_cell*_press_grad[_qp].size()+eps;
      break;
    case ST:
      norm = 0.5*(h_cell*_press_grad[_qp].size()+std::fabs(_press[_qp]));
      break;      
    default:
      mooseError("'" << this->name() << "': invalid viscosity type. The options are: JST, HMP and ST");
      break;
  }

  // Pre-compute the viscosity coefficient
  Real kappa = (std::fabs(_norm_vel[_qp])+std::sqrt(c2))*std::fabs(_press_laplace[_qp])/norm;

  // Set material viscosity coefficient
  _kappa_max[_qp] = 0.5*h_cell*(hU.size()/_h[_qp]+std::sqrt(c2));
  _kappa[_qp] = std::min(_Ce*h_cell*h_cell*h_cell*kappa, _kappa_max[_qp]);
}