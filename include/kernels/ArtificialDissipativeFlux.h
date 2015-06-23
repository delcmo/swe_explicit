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

#ifndef ARTIFICIALDISSIPATIVEFLUX_H
#define ARTIFICIALDISSIPATIVEFLUX_H

#include "Kernel.h"

// Forward Declarations
class ArtificialDissipativeFlux;

template<>
InputParameters validParams<ArtificialDissipativeFlux>();

class ArtificialDissipativeFlux : public Kernel
{
public:

  ArtificialDissipativeFlux(const std::string & name,
             InputParameters parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int _jvar);
    
private:
  
  // Equation type
  enum EquationType
  {
      continuity = 0,
      x_mom = 1,
      y_mom = 2
  };
  MooseEnum _equ_type;

  // Material.
  const MaterialProperty<Real> & _kappa;
};

#endif // ARTIFICIALDISSIPATIVEFLUX_H
