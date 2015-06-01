#ifndef SAINTVENANTSETWATERVELOCITYOUTETBC_H
#define SAINTVENANTSETWATERVELOCITYOUTETBC_H

#include "IntegratedBC.h"

// Forward Declarations
class SaintVenantSetWaterVelocityOutletBC;
class EquationOfState;

template<>
InputParameters validParams<SaintVenantSetWaterVelocityOutletBC>();

class SaintVenantSetWaterVelocityOutletBC : public IntegratedBC
{
public:
  SaintVenantSetWaterVelocityOutletBC(const std::string & name, InputParameters parameters);
  virtual ~SaintVenantSetWaterVelocityOutletBC(){}

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
  Real _u_bc;

  // Equation of state
  const EquationOfState & _eos;

  // Integers for jacobian terms
  unsigned _h_var;
  unsigned _hu_var;
};

#endif // SAINTVENANTSETWATERVELOCITYOUTETBC_H

