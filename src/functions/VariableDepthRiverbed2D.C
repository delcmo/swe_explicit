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

#include "VariableDepthRiverbed2D.h"

template<>
InputParameters validParams<VariableDepthRiverbed2D>()
{
  InputParameters params = validParams<Function>();

  // Parameters
  params.addParam<Real>("xmin", 0., "Minimum value");
  params.addParam<Real>("xmax", 1., "Maximum value");
  params.addParam<Real>("ymin", 0., "Minimum value");
  params.addParam<Real>("ymax", 1., "Maximum value");

  return params;
}

VariableDepthRiverbed2D::VariableDepthRiverbed2D(const std::string & name, InputParameters parameters) :
    Function(name, parameters),
    // parameters
    _xmin(getParam<Real>("xmin")),
    _xmax(getParam<Real>("xmax")),
    _ymin(getParam<Real>("ymin")),
    _ymax(getParam<Real>("ymax"))
{}

Real
VariableDepthRiverbed2D::value(Real /*t*/, const Point & p)
{
  if ( p(0)<_xmin || p(1)<_ymin )
    return 0.;
  else if ( p(0)>_xmax || p(1)>_ymax )
    return 0.;
  else
    return std::sin(libMesh::pi*(p(0)-_xmin)/(_xmax-_xmin))*std::sin(libMesh::pi*(p(1)-_ymin)/(_ymax-_ymin));
}

RealVectorValue
VariableDepthRiverbed2D::gradient(Real /*t*/, const Point & p)
{
  return 0.;
}
