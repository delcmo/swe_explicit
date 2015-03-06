#ifndef LAPIDUSVISCOSITYCOEFFICIENT_H
#define LAPIDUSVISCOSITYCOEFFICIENT_H

#include "Material.h"
#include "EquationOfState.h"

class LapidusViscosityCoefficient;

template<>
InputParameters validParams<LapidusViscosityCoefficient>();

/**
 * Computes dissipative fluxes for entropy viscosity method
 */
class LapidusViscosityCoefficient : public Material
{
public:
  LapidusViscosityCoefficient(const std::string & name, InputParameters parameters);
  virtual ~LapidusViscosityCoefficient();

protected:
  virtual void computeQpProperties();

  // Coupled variables
  VariableValue & _h;
  VariableValue & _hu;

  // Coupled gradient
  VariableGradient & _vel_grad;

  // Lapidus parameter
  Real _Ce;

  // Equation of state
  const EquationOfState & _eos;

  // material to compute
  MaterialProperty<Real> & _kappa;
  MaterialProperty<Real> & _kappa_max;
};

#endif /* LAPIDUSVISCOSITYCOEFFICIENT_H */
