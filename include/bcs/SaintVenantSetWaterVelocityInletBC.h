#ifndef SAINTVENANTSETWATERVELOCITYINLETBC_H
#define SAINTVENANTSETWATERVELOCITYINLETBC_H

#include "IntegratedBC.h"
#include "Function.h"

// Forward Declarations
class SaintVenantSetWaterVelocityInletBC;
class EquationOfState;

template<>
InputParameters validParams<SaintVenantSetWaterVelocityInletBC>();

class SaintVenantSetWaterVelocityInletBC : public IntegratedBC
{
public:
  SaintVenantSetWaterVelocityInletBC(const std::string & name, InputParameters parameters);
  virtual ~SaintVenantSetWaterVelocityInletBC(){}

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
  Real _h_bc;

  // Equation of state
  const EquationOfState & _eos;

  // Integers for jacobian terms
  unsigned _h_var;
  unsigned _hu_var;

  // boolean
  bool _h_bc_specified;
};

#endif // SAINTVENANTSETWATERVELOCITYINLETBC_H

