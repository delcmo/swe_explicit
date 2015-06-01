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

#include "VariableDepthRiverbed1D.h"

template<>
InputParameters validParams<VariableDepthRiverbed1D>()
{
  InputParameters params = validParams<Function>();

  // x-boundaries
  params.addParam<Real>("xmin", 0., "Minimum value");
  params.addParam<Real>("xmax", 1., "Maximum value");
  // maximum value of the topology
  params.addParam<Real>("amplitude", 1., "Maximum value of the topology");

  return params;
}

VariableDepthRiverbed1D::VariableDepthRiverbed1D(const std::string & name, InputParameters parameters) :
    // x-boundaries
    Function(name, parameters),
    _xmin(getParam<Real>("xmin")),
    _xmax(getParam<Real>("xmax")),
    // maximum value of the topology
    _amplitude(getParam<Real>("amplitude"))
{}

Real
VariableDepthRiverbed1D::value(Real /*t*/, const Point & p)
{
  if ( p(0)<_xmin )
    return 0.;
  else if ( p(0)>_xmax )
    return 0.;
  else
    return _amplitude*std::sin(libMesh::pi*(p(0)-_xmin)/(_xmax-_xmin));
}

RealVectorValue
VariableDepthRiverbed1D::gradient(Real /*t*/, const Point & p)
{
  if ( p(0)<_xmin )
    return 0.;
  else if ( p(0)>_xmax )
    return 0.;
  else
    return _amplitude*libMesh::pi/(_xmax-_xmin)*std::sin(libMesh::pi*(p(0)-_xmin));
}
