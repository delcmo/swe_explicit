#ifndef SOLIDWALLBC_H
#define SOLIDWALLBC_H

#include "IntegratedBC.h"

// Forward Declarations
class SolidWallBC;
class EquationOfState;

template<>
InputParameters validParams<SolidWallBC>();

class SolidWallBC : public IntegratedBC
{
public:
  SolidWallBC(const std::string & name, InputParameters parameters);
  virtual ~SolidWallBC(){}

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  // Equation type
  enum EquationType
  {
    continuity = 0,
    x_mom = 1,
    y_mom = 2
  };
  MooseEnum _equ_type;

  // Coupled variables
  VariableValue & _h;

  // Equation of state
  const EquationOfState & _eos;

  // Integers for jacobian terms
  unsigned _h_var;
  unsigned _hu_var;
  unsigned _hv_var;
};

#endif // SOLIDWALLBC_H

