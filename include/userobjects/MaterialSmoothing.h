#ifndef MATERIALSMOOTHING_H
#define MATERIALSMOOTHING_H

#include "SideUserObject.h"

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
class MaterialSmoothing : public SideUserObject
{
public:
  // Constructor
  MaterialSmoothing(const std::string & name, InputParameters parameters);

  // Destructor
  virtual ~MaterialSmoothing();

  /**
   * Called when this object needs to compute something.
   */
  virtual void execute() {};

  /**
   * Called before execute() is ever called so that data can be cleared.
   */
  virtual void initialize(){};

protected:
  std::string _var_name;  
};


#endif // MATERIALSMOOTHING_H

