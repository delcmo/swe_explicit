[GlobalParams]
[]

[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = -5.
  xmax = 5.
  nx = 200
[]

[Functions]
  [./ic_func]
    axis = 0
    type = PiecewiseLinear
    x = '-5  0  0.0001 5'
    y = '3 3  1  1'
  [../]
[]

[UserObjects]
  [./hydro]
    type = HydrostaticPressure
    gravity = 1.
  [../]
  
  [./jump]
    type = JumpInterface
    entropy_flux_x = F_aux
    var_name_jump = jump_aux
  [../]
[]

[Variables]
  [./h]
    family = LAGRANGE
    order = FIRST
    [./InitialCondition]
      type = FunctionIC
      function = ic_func
    [../]
  [../]

  [./hu]
    family = LAGRANGE
    order = FIRST  
    [./InitialCondition]
      type = ConstantIC
      value = 0.
    [../]
  [../]
[]

[Kernels]
  [./TimeMass]
    type = LumpedTimeDerivative
    variable = h
    implicit = true    
  [../]

  [./Mass]
    type = WaterHeightEqu
    variable = h
    hu = hu
    implicit = false
  [../]

  [./ArtDiffMass]
    type = ArtificialDissipativeFlux
    variable = h
    equ_name = continuity
    implicit = false
  [../]

  [./TimeMmom]
    type = LumpedTimeDerivative
    variable = hu
    implicit = true
  [../]

  [./Momentum]
    type = MomentumEqu
    variable = hu
    h = h
    hu = hu
    component = 0
    eos = hydro
    implicit = false    
  [../]
  
  [./ArtDiffMom]
    type = ArtificialDissipativeFlux
    variable = hu
    equ_name = x_mom
    implicit = false    
  [../]
[]

[AuxVariables]
  [./u_aux]
    family = LAGRANGE
    order = FIRST
  [../]

  [./entropy_aux]
    family = LAGRANGE
    order = FIRST
  [../]

  [./F_aux]
    family = LAGRANGE
    order = FIRST
  [../]
  
  [./froude_aux]
    family = LAGRANGE
    order = FIRST
  [../]

  [./kappa_aux]
    family = MONOMIAL
    order = CONSTANT
  [../]

  [./kappa_max_aux]
    family = MONOMIAL
    order = CONSTANT
  [../]
  
  [./residual_aux]
    family = MONOMIAL
    order = CONSTANT
  [../]
  
  [./jump_aux]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
  [./u_ak]
    type = Xvelocity
    variable = u_aux
    h = h
    hu = hu
  [../]

  [./entropy_ak]
    type = EnergySw
    variable = entropy_aux
    h = h
    hu = hu
    eos = hydro    
  [../]

  [./F_ak]
    type = EnergyFluxSw
    variable = F_aux
    momentum = hu
    h = h
    hu = hu
    eos = hydro    
  [../]
  
  [./froude_ak]
    type = FroudeNumberAux
    variable = froude_aux
    h = h
    hu = hu
    eos = hydro    
  [../]

  [./kappa_ak]
    type = MaterialRealAux
    variable = kappa_aux
    property = kappa
  [../]

  [./kappa_max_ak]
    type = MaterialRealAux
    variable = kappa_max_aux
    property = kappa_max
  [../]
 
  [./residual_ak]
    type = MaterialRealAux
    variable = residual_aux
    property = residual
  [../]
[]

[Materials]
  [./EntropyViscosityCoeff]
    type = EntropyViscosityCoefficient
    block = 0
    is_first_order = true
    Ce = 1.
    h = h
    hu = hu
    entropy = entropy_aux
    F = F_aux
    eos = hydro
  [../]
[]

[BCs]
 active='h_bc_left h_bc_right hu_bc_left hu_bc_right'
  [./h_bc_left]
    type = SaintVenantSetWaterHeightOutletBC
    variable = h
    boundary = left
    equ_name = continuity
    h = h
    hu = hu
    h_bc = 3
    eos = hydro
    implicit = true 
  [../]

  [./h_bc_right]
    type = SaintVenantSetWaterHeightOutletBC
    variable = h
    boundary = right
    equ_name = continuity
    h = h
    hu = hu
    h_bc = 1
    eos = hydro
    implicit = true
  [../]

  [./hu_bc_left]
    type = SaintVenantSetWaterHeightOutletBC
    variable = hu
    boundary = left
    equ_name = x_mom
    h = h
    hu = hu
    h_bc = 3.
    eos = hydro
    implicit = true
  [../]

  [./hu_bc_right]
    type = SaintVenantSetWaterHeightOutletBC
    variable = hu
    boundary = right
    equ_name = x_mom
    h = h
    hu = hu
    h_bc = 1
    eos = hydro
    implicit = true
  [../]

  [./h_bc_wall]
    type = SolidWallBC
    variable = h
    boundary = 'right left'
    equ_name = continuity
    h = h
    hu = hu
    eos = hydro
    implicit = true
  [../]

  [./hu_bc_wall]
    type = SolidWallBC
    variable = hu
    boundary = 'right left'
    equ_name = x_mom
    h = h
    hu = hu
    eos = hydro
    implicit = true
  [../]
[]

[Postprocessors]
  [./dt]
    type = TimeStepCFL
    h = h
    hu = hu
    eos = hydro
    cfl = 0.2
    outputs = none
  [../]
[]

[Executioner]
  type = Transient
  scheme = 'explicit-euler' # 'rk-2'
  solve_type = 'LINEAR'
  dt = 1e-4
  
  [./TimeStepper]
    type = PostprocessorDT
    postprocessor = dt
    dt = 1.e-5
  [../]

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-10
#  nl_max_its = 10

  end_time = 2.
#  num_steps = 20

  [./Quadrature]
   type = GAUSS
    order = SECOND
  [../]

[]

[Outputs]
  output_initial = true
  exodus = true
  print_linear_residuals = false
  print_perf_log = true
  interval = 1
[]