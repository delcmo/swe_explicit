#ifndef SAINTVENANTSETWATERMOMENTUMOUTLETBC_H
#define SAINTVENANTSETWATERMOMENTUMOUTLETBC_H

#include "IntegratedBC.h"
#include "Function.h"

// Forward Declarations
class SaintVenantSetWaterMomentumOutletBC;
class EquationOfState;

template<>
InputParameters validParams<SaintVenantSetWaterMomentumOutletBC>();

class SaintVenantSetWaterMomentumOutletBC : public IntegratedBC
{
public:
  SaintVenantSetWaterMomentumOutletBC(const std::string & name, InputParameters parameters);
  virtual ~SaintVenantSetWaterMomentumOutletBC(){}

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
  Real _hu_bc;

  // Equation of state
  const EquationOfState & _eos;

  // Integers for jacobian terms
  unsigned _h_var;
  unsigned _hu_var;
};

#endif // SAINTVENANTSETWATERMOMENTUMOUTLETBC_H

