[GlobalParams]
is_first_order = false
Ce = 1.
Cjump = 4.1
[]

[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = -5.
  xmax = 5.
  nx = 400
[]

[Functions]
  [./ic_func]
    axis = 0
    type = PiecewiseLinear
    x = '-5  0  0.0001 5'
    y = ' 3  3  1    1'
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
    execute_on = timestep_begin
  [../]

  [./jump-smooth]
    type = MaterialSmoothing
    smoothing_fct_name = average
    variable = jump_aux
    var_name = jump_smooth_aux
    execute_on = timestep_begin
  [../]

  [./jump-smooth-bis]
   type = MaterialSmoothing
   smoothing_fct_name = average
   variable = jump_smooth_aux
   var_name = jump_smooth_bis_aux
   execute_on = timestep_begin
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
    type = TimeDerivative
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
    type = TimeDerivative
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

  [./jump_smooth_aux]
    family = MONOMIAL
    order = CONSTANT
  [../]

  [./jump_smooth_bis_aux]
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
    h = h
    hu = hu
    entropy = entropy_aux
    F = F_aux
    jump_entropy_flux = jump_smooth_bis_aux
    eos = hydro
  [../]
[]

[BCs]
  [./h_bc_left]
    type = DirichletBC
    variable = h
    value = 3.
    boundary = left
  [../]

  [./h_bc_right]
    type = DirichletBC
    variable = h
    value = 1.
    boundary = right
  [../]

  [./hu_bc_left]
    type = DirichletBC
    variable = hu
    value = 0.
    boundary = left
  [../]

  [./hu_bc_right]
    type = DirichletBC
    variable = hu
    value = 0.
    boundary = right
  [../]
[]

[Postprocessors]
  [./dt]
    type = TimeStepCFL
    h = h
    hu = hu
    eos = hydro
    cfl = 1.
#    outputs = none
  [../]
[]

[Executioner]
  type = Transient
  scheme = 'explicit-euler'
  solve_type = 'LINEAR'
  dt = 1.e-3
  
#  [./TimeStepper]
#    type = PostprocessorDT
#    postprocessor = dt
#    dt = 1.e-5
#  [../]

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-10
  nl_max_its = 2

  end_time = 2.
  num_steps = 200000

  [./Quadrature]
   type = GAUSS
    order = SECOND
  [../]

[]

[Outputs]
  output_initial = true
  output_final = true
  exodus = true
  print_linear_residuals = false
  print_perf_log = true
  interval = 1
[]