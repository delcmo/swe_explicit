#ifndef SAINTVENANTSETWATERMOMENTUMINLETBC_H
#define SAINTVENANTSETWATERMOMENTUMINLETBC_H

#include "IntegratedBC.h"
#include "Function.h"

// Forward Declarations
class SaintVenantSetWaterMomentumInletBC;
class EquationOfState;

template<>
InputParameters validParams<SaintVenantSetWaterMomentumInletBC>();

class SaintVenantSetWaterMomentumInletBC : public IntegratedBC
{
public:
  SaintVenantSetWaterMomentumInletBC(const std::string & name, InputParameters parameters);
  virtual ~SaintVenantSetWaterMomentumInletBC(){}

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
  VariableValue & _hu;

  // Constants and parameters
  Real _h_bc;
  Real _hu_bc;

  // Equation of state
  const EquationOfState & _eos;

  // Integers for jacobian terms
  unsigned _h_var;
  unsigned _hu_var;

  // boolean
  bool _h_bc_specified;
};

#endif // SAINTVENANTSETWATERMOMENTUMINLETBC_H

