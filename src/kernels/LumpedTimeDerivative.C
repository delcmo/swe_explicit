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

#include "LumpedTimeDerivative.h"

template<>
InputParameters validParams<LumpedTimeDerivative>()
{
  InputParameters params = validParams<TimeKernel>();
  return params;
}

LumpedTimeDerivative::LumpedTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeKernel(name, parameters),
    // get the nodal values
    _u_nodal(_var.nodalValue()),
    _u_old_nodal(_var.nodalValueOld())
{
}

Real
LumpedTimeDerivative::computeQpResidual()
{
  return _test[_i][_qp]*_u_dot[_qp];
}

Real
LumpedTimeDerivative::computeQpJacobian()
{
  return _test[_i][_qp]*_phi[_j][_qp]*_du_dot_du[_qp];
}

void
LumpedTimeDerivative::computeResidual()
{
  DenseVector<Number> & re = _assembly.residualBlock(_var.number(), Moose::KT_TIME);
  _local_re.resize(re.size());
  _local_re.zero();

  precalculateResidual();
  for (_i = 0; _i < _test.size(); _i++)
    for (_j = 0; _j < _phi.size(); _j++)
      for (_qp = 0; _qp < _qrule->n_points(); _qp++)
        _local_re(_i) += _JxW[_qp] * _coord[_qp] * (_u_nodal[_i]-_u_old_nodal[_i]) * _phi[_j][_qp] * _test[_i][_qp] / _dt;

  re += _local_re;

  if (_has_save_in)
  {
    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (unsigned int i=0; i<_save_in.size(); i++)
      _save_in[i]->sys().solution().add_vector(_local_re, _save_in[i]->dofIndices());
  }
}

void
LumpedTimeDerivative::computeJacobian()
{
  DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());

  for (_i = 0; _i < _test.size(); _i++)
    for (_j = 0; _j < _phi.size(); _j++)
      for (_qp = 0; _qp < _qrule->n_points(); _qp++)
      {
        ke(_i, _i) += _JxW[_qp] * _coord[_qp] * computeQpJacobian();
      }
}
