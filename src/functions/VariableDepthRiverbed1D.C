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
  params.addParam<Real>("xmin", 0., "Minimum value");
  params.addParam<Real>("xmax", 1., "Maximum value");
  return params;
}

VariableDepthRiverbed1D::VariableDepthRiverbed1D(const std::string & name, InputParameters parameters) :
    Function(name, parameters),
    _xmin(getParam<Real>("xmin")),
    _xmax(getParam<Real>("xmax"))
{}

Real
VariableDepthRiverbed1D::value(Real /*t*/, const Point & p)
{
  if ( p(0)<_xmin )
    return 0.;
  else if ( p(0)>_xmax )
    return 0.;
  else
    return (std::cos(10*libMesh::pi*(p(0)-0.5))+1)/8.;
}

RealVectorValue
VariableDepthRiverbed1D::gradient(Real /*t*/, const Point & p)
{
  if ( p(0)<_xmin )
    return 0.;
  else if ( p(0)>_xmax )
    return 0.;
  else
    return -10*libMesh::pi*std::sin(10*libMesh::pi*(p(0)-0.5))/8.;
}
