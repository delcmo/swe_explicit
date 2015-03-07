#include "MaterialSmoothing.h"
#include "MooseError.h"

template<>
InputParameters validParams<MaterialSmoothing>()
{
  InputParameters params = validParams<SideUserObject>();

  params.addRequiredParam<std::string>("var_name", "the name of the variable that will store the smoothed variable.");

  return params;
}

MaterialSmoothing::MaterialSmoothing(const std::string & name, InputParameters parameters) :
    SideUserObject(name, parameters),
    _var_name(getParam<std::string>("var_name"))
{}

MaterialSmoothing::~MaterialSmoothing()
{
  // Destructor, empty
}