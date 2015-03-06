#include "LapidusViscosityCoefficient.h"

template<>
InputParameters validParams<LapidusViscosityCoefficient>()
{
  InputParameters params = validParams<Material>();
  
  // Coupled variables
  params.addRequiredCoupledVar("h", "high/density");
  params.addRequiredCoupledVar("hu", "x component of h*vec{u}");
  // Coupled aux variables
  params.addRequiredCoupledVar("u", "x-component of the fluid velocity");  
  // Lapidus parameter
  params.addParam<Real>("Ce", 1., "Constant that multiplies the viscosity coefficient");
  // Equation of state
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");

  return params;
}

LapidusViscosityCoefficient::LapidusViscosityCoefficient(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    // Coupled variables
    _h(coupledValue("h")),
    _hu(coupledValue("hu")),
    // Coupled aux variable
    _vel_grad(coupledGradient("u")),
    // Lapidus parameter
    _Ce(getParam<Real>("Ce")),
    // Equation of state:
    _eos(getUserObject<EquationOfState>("eos")),
    // Materials
    _kappa(declareProperty<Real>("kappa")),
    _kappa_max(declareProperty<Real>("kappa_max"))
{
  if (_mesh.dimension()!=1)
    mooseError("'" << this->name() << "' can only be used with 1-D mesh.");
}

LapidusViscosityCoefficient::~LapidusViscosityCoefficient()
{
}

void
LapidusViscosityCoefficient::computeQpProperties()
{
  // Cell size
  Real h_cell = _current_elem->hmin();

  // Speed of sound
  RealVectorValue hU(_hu[_qp], 0., 0.);
  Real c2=_eos.c2(_h[_qp], hU);

  // Set material viscosity coefficient
  _kappa_max[_qp] = 0.5*h_cell*(hU.size()/_h[_qp]+std::sqrt(c2));
  _kappa[_qp] = std::min(_Ce*h_cell*h_cell*std::fabs(_vel_grad[_qp](0)), _kappa_max[_qp]);
}