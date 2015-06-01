#include "SweExplicitApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

// kernels
#include "LumpedTimeDerivative.h"
#include "WaterHeightEqu.h"
#include "MomentumEqu.h"
#include "ArtificialDissipativeFlux.h"
#include "PressureBasedViscosityMassMatrix.h"
#include "PressureBasedViscosityLaplace.h"

// auxkernels
#include "Xvelocity.h"
#include "PressureSw.h"
#include "EnergySw.h"
#include "EnergyFluxSw.h"

// ics
#include "StepIC.h"
#include "IcsWithTopology1D.h"

// bcs
#include "SaintVenantSetWaterHeightInletBC.h"
#include "SaintVenantSetWaterHeightOutletBC.h"
#include "SaintVenantSetWaterVelocityInletBC.h"
#include "SaintVenantSetWaterVelocityOutletBC.h"
#include "SaintVenantSetWaterMomentumInletBC.h"
#include "SaintVenantSetWaterMomentumOutletBC.h"
#include "SolidWallBC.h"

// eos
#include "EquationOfState.h"
#include "HydrostaticPressure.h"

// userobjects
#include "MaterialSmoothing.h"
#include "JumpInterface.h"

// materials
#include "EntropyViscosityCoefficient.h"
#include "LapidusViscosityCoefficient.h"
#include "PressureBasedViscosityCoefficient.h"

// posprocessors
#include "TimeStepCFL.h"

// functions
#include "VariableDepthRiverbed1D.h"
#include "VariableDepthRiverbed2D.h"

template<>
InputParameters validParams<SweExplicitApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

SweExplicitApp::SweExplicitApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  SweExplicitApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  SweExplicitApp::associateSyntax(_syntax, _action_factory);
}

SweExplicitApp::~SweExplicitApp()
{
}

extern "C" void SweExplicitApp__registerApps() { SweExplicitApp::registerApps(); }
void
SweExplicitApp::registerApps()
{
  registerApp(SweExplicitApp);
}

void
SweExplicitApp::registerObjects(Factory & factory)
{
  // kernels
  registerKernel(LumpedTimeDerivative);
  registerKernel(WaterHeightEqu);
  registerKernel(MomentumEqu);
  registerKernel(ArtificialDissipativeFlux);
  registerKernel(PressureBasedViscosityMassMatrix);
  registerKernel(PressureBasedViscosityLaplace);

  // auxkernels
  registerAux(Xvelocity);
  registerAux(PressureSw);
  registerAux(EnergySw);
  registerAux(EnergyFluxSw);

  // ics
  registerInitialCondition(StepIC);
  registerInitialCondition(IcsWithTopology1D);

  // bcs
  registerBoundaryCondition(SaintVenantSetWaterHeightInletBC);
  registerBoundaryCondition(SaintVenantSetWaterHeightOutletBC);
  registerBoundaryCondition(SaintVenantSetWaterVelocityInletBC);
  registerBoundaryCondition(SaintVenantSetWaterVelocityOutletBC);
  registerBoundaryCondition(SaintVenantSetWaterMomentumInletBC);
  registerBoundaryCondition(SaintVenantSetWaterMomentumOutletBC);
  registerBoundaryCondition(SolidWallBC);

  // eos
  registerUserObject(EquationOfState);
  registerUserObject(HydrostaticPressure);

  // userobjects
  registerUserObject(MaterialSmoothing);
  registerUserObject(JumpInterface);

  // materials
  registerMaterial(EntropyViscosityCoefficient);
  registerMaterial(LapidusViscosityCoefficient);
  registerMaterial(PressureBasedViscosityCoefficient);

  // postprocessors
  registerPostprocessor(TimeStepCFL);

  // functions
  registerFunction(VariableDepthRiverbed1D);
  registerFunction(VariableDepthRiverbed2D);
}

void
SweExplicitApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
