#include "MaterialSmoothing.h"
#include "MooseError.h"

template<>
InputParameters validParams<MaterialSmoothing>()
{
  InputParameters params = validParams<SideUserObject>();
  return params;
}

MaterialSmoothing::MaterialSmoothing(const std::string & name, InputParameters parameters) :
    SideUserObject(name, parameters)
{}

MaterialSmoothing::~MaterialSmoothing()
{
  // Destructor, empty
}