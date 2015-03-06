/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "StepIC.h"

template<>
InputParameters validParams<StepIC>()
{
    InputParameters params = validParams<InitialCondition>();
    // Initial conditions:
    params.addRequiredParam<Real>("h_left", "Initial water height on the left");
    params.addRequiredParam<Real>("h_right", "Initial water height on the right");
    params.addParam<RealVectorValue>("U_left", (0., 0., 0.), "Initial velocity vector on the left");
    params.addParam<RealVectorValue>("U_right", (0., 0., 0.), "Inital velocity vector on the right");
    // Position of the center of the circle and its radius:
    params.addRequiredParam<Real>("x_source", "Position of the point source: x");
    params.addRequiredParam<Real>("y_source", "Position of the point source: y");
    params.addRequiredParam<Real>("radius", "Radius of the circle");
    return params;
}

StepIC::StepIC(const std::string & name,
                     InputParameters parameters) :
    InitialCondition(name, parameters),
	// IC parameters
    _h_left(getParam<Real>("h_left")),
    _h_right(getParam<Real>("h_right")),
    _U_left(getParam<RealVectorValue>("U_left")),
    _U_right(getParam<RealVectorValue>("U_right")),
    // Position of the membrane:
    _x_source(getParam<Real>("x_source")),
    _y_source(getParam<Real>("y_source")),
    _radius(getParam<Real>("radius"))
{}

Real
StepIC::value(const Point & p)
{
  // Name of the variable to initialize
  std::string name_var = _var.name();
      
  // Determine the initial values based on the node coordinates
  Real h, hu, hv;
  Real radius2 = (p(0)-_x_source)*(p(0)-_x_source) + (p(1)-_y_source)*(p(1)-_y_source);
      
  if ( std::sqrt(radius2) <= _radius )
  {
    h=_h_left;
    hu=_h_left*_U_left(0);
    hv=_h_left*_U_left(1);
  }
  else
  {
    h=_h_right;
    hu=_h_right*_U_right(0);
    hv=_h_right*_U_right(1);
  }

  // Return value
  if ( name_var == "h" ) // Water height 'h'
    return h;
  else if ( name_var == "hu" ) // x-component of momentum 'hu'
    return hu;
  else if ( name_var == "hv" ) // y-component of momentum 'hv'
    return hv;
  else
    mooseError("'" << this->name() << "': this function requires the name of the variables to be 'h', 'hu' and 'hv'.");
}
