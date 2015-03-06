#ifndef SAINTVENANTSETWATERHEIGHTOUTLETBC_H
#define SAINTVENANTSETWATERHEIGHTOUTLETBC_H

#include "IntegratedBC.h"
#include "Function.h"

// Forward Declarations
class SaintVenantSetWaterHeightOutletBC;
class EquationOfState;

template<>
InputParameters validParams<SaintVenantSetWaterHeightOutletBC>();


/**
**/
class SaintVenantSetWaterHeightOutletBC : public IntegratedBC
{
public:
  SaintVenantSetWaterHeightOutletBC(const std::string & name, InputParameters parameters);
  virtual ~SaintVenantSetWaterHeightOutletBC(){}

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

  // Equation of state
  const EquationOfState & _eos;

  // Integers for jacobian terms
  unsigned _h_var;  
  unsigned _hu_var;
};

#endif // SAINTVENANTSETWATERHEIGHTOUTLETBC_H

