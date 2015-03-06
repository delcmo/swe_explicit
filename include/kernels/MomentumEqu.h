#ifndef MOMENTUMEQU_H
#define MOMENTUMEQU_H

#include "Kernel.h"
#include "EquationOfState.h"

//Forward Declarations
class MomentumEqu;

template<>
InputParameters validParams<MomentumEqu>();

class MomentumEqu : public Kernel
{
public:

  MomentumEqu(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  VariableValue & _h;
  VariableValue & _hu;
  VariableValue & _hv;

  VariableGradient & _b_grad;

  Real _g;
  unsigned int _component;

  const EquationOfState & _eos;

  unsigned int _h_var;
  unsigned int _hu_var;
  unsigned int _hv_var;
};

#endif