#ifndef SAINTVENANTSETWATERHEIGHTINLETBC_H
#define SAINTVENANTSETWATERHEIGHTINLETBC_H

#include "IntegratedBC.h"
#include "Function.h"

// Forward Declarations
class SaintVenantSetWaterHeightInletBC;
class EquationOfState;

template<>
InputParameters validParams<SaintVenantSetWaterHeightInletBC>();


/**
**/
class SaintVenantSetWaterHeightInletBC : public IntegratedBC
{
public:
  SaintVenantSetWaterHeightInletBC(const std::string & name, InputParameters parameters);
  virtual ~SaintVenantSetWaterHeightInletBC(){}

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
  VariableValue & _hu;

  // Constants and parameters
  Real _h_bc;
  Real _u_bc;

  // Equation of state
  const EquationOfState & _eos;

  // Integers for jacobian terms
  unsigned _hu_var;

  // boolean
  bool _u_bc_specified;
};

#endif // SAINTVENANTSETWATERHEIGHTINLETBC_H

