#ifndef PRESSUREBASEDVISCOSITYCOEFFICIENT_H
#define PRESSUREBASEDVISCOSITYCOEFFICIENT_H

#include "Material.h"
#include "EquationOfState.h"

class PressureBasedViscosityCoefficient;

template<>
InputParameters validParams<PressureBasedViscosityCoefficient>();

/**
 * Computes dissipative fluxes for entropy viscosity method
 */
class PressureBasedViscosityCoefficient : public Material
{
public:
  PressureBasedViscosityCoefficient(const std::string & name, InputParameters parameters);
  virtual ~PressureBasedViscosityCoefficient();

protected:
  virtual void computeQpProperties();

  // Pressure-based viscosity type:
  enum PBVtype
  {
    JST = 0,
    HMP = 1,
    ST = 2
  };
  MooseEnum _pbv_type;

  // Coupled variable
  VariableValue & _h;
  VariableValue & _hu;
  VariableValue & _hv;
  VariableValue & _press_laplace;

  // Coupled aux variable
  VariableValue & _press;
  VariableGradient & _press_grad;
  VariableValue & _norm_vel;
  
  // Lapidus parameter
  Real _Ce;

  // Equation of state
  const EquationOfState & _eos;

  // material to compute
  MaterialProperty<Real> & _kappa;
  MaterialProperty<Real> & _kappa_max;
};

#endif /* PRESSUREBASEDVISCOSITYCOEFFICIENT_H */
