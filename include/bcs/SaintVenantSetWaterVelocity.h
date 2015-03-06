#ifndef SAINTVENANTSETWATERVELOCITY_H
#define SAINTVENANTSETWATERVELOCITY_H

#include "IntegratedBC.h"
#include "Function.h"

// Forward Declarations
class SaintVenantSetWaterVelocity;
class EquationOfState;

template<>
InputParameters validParams<SaintVenantSetWaterVelocity>();

class SaintVenantSetWaterVelocity : public IntegratedBC
{
public:
  SaintVenantSetWaterVelocity(const std::string & name, InputParameters parameters);
  virtual ~SaintVenantSetWaterVelocity(){}

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  // Equation type
  enum EquationType
  {
    continuity = 0,
    x_mom = 1
  };
  MooseEnum _equ_type;

  // Coupled variables
  VariableValue & _h;

  // Constants and parameters
  Real _u_bc;

  // Equation of state
  const EquationOfState & _eos;

  // Integers for jacobian terms
  unsigned _h_var;
  unsigned _hu_var;
};

#endif // SAINTVENANTSETWATERVELOCITY_H

