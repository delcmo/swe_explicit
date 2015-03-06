#ifndef WATERHEIGHTEQU_H
#define WATERHEIGHTEQU_H

#include "Kernel.h"

//Forward Declarations
class WaterHeightEqu;

template<>
InputParameters validParams<WaterHeightEqu>();

class WaterHeightEqu : public Kernel
{
public:

  WaterHeightEqu(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  VariableValue & _hu;
  VariableValue & _hv;

  unsigned int _hu_var;
  unsigned int _hv_var;
};

#endif
