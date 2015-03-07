#ifndef MATERIALSMOOTHING_H
#define MATERIALSMOOTHING_H

#include "InternalSideUserObject.h"

// Forward Declarations
class MaterialSmoothing;

template<>
InputParameters validParams<MaterialSmoothing>();


/**
 * The MaterialSmoothing object is responsible for
 * computing and returning:
 * p = p(h, hU) where hU = (hu, hv) is the momentum vector
 * and various derivatives.
 *
 * We derive from UserObject so we can have a validParams()
 * function and be registered in the factory.
 */
class MaterialSmoothing : public InternalSideUserObject
{
public:
  // Constructor
  MaterialSmoothing(const std::string & name, InputParameters parameters);

  // Destructor
  virtual ~MaterialSmoothing();

  virtual void initialize();
  virtual void execute();
  virtual void destroy();
  virtual void finalize();
  virtual void threadJoin(const UserObject & uo);

  Real getValue() const { return _value; }  

protected:
  // Auxiliary system variable:
  AuxiliarySystem & _aux;
  // Gradient value:
  VariableGradient & _grad_u;
  VariableGradient & _grad_u_neighbor;
  // Name of the variable storing the jump:
  std::string _var_name;
  // Temporary variable:
  Real _value;
};


#endif // MATERIALSMOOTHING_H

