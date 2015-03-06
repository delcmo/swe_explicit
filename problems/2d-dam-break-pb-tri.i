[Mesh]
  dim = 2
  file=partial-dam-break-tri-2.e
  uniform_refine = 0
[]

[Functions]
  [./topology]
    type = ConstantFunction
    value = 0.
  [../]
  
  [./ic_func]
    axis = 0
    type = PiecewiseLinear
    x = '-700  -5.   -4.9  700'
    y = '10    10   9.5    9.5'
  [../]
[]

[UserObjects]
  [./hydro]
    type = HydrostaticPressure
    gravity = 9.8
  [../]
[]

[Variables]
  [./h]
    family = LAGRANGE
    order = first
    [./InitialCondition]
      type = FunctionIC
      function = ic_func
    [../]
  [../]

  [./hu]
    family = LAGRANGE
    order = first  
    [./InitialCondition]
    type = ConstantIC
    value = 0.
    [../]
  [../]
  
  [./hv]
    family = LAGRANGE
    order = first  
    [./InitialCondition]
    type = ConstantIC
    value = 0.
    [../]
  [../]
[]

[Kernels]
  # Water height equation
  [./TimeMass]
    type = TimeDerivative
    variable = h
  [../]

  [./Mass]
    type = WaterHeightEqu
    variable = h
    hu = hu
    hv = hv
  [../]
  
  [./MassDissip]
    type = ArtificialDissipativeFlux
    variable = h
    equ_name = continuity
  [../]

  # x-momentum equation
  [./TimeXMom]
    type = TimeDerivative
    variable = hu
  [../]

  [./XMomentum]
  type = MomentumEqu
  variable = hu
  h = h
  hu = hu
  hv = hv  
  gravity = 9.8
  component = 0
  topology = topology
  eos = hydro
  [../]

  [./XMomDissip]
    type = ArtificialDissipativeFlux
    variable = hu
    equ_name = x_mom
  [../]

  # y-momentum equation  
  [./TimeYMom]
    type = TimeDerivative
    variable = hv
  [../]

  [./YMomentum]
  type = MomentumEqu
  variable = hv
  h = h
  hu = hu
  hv = hv
  gravity = 9.8
  component = 1
  topology = topology
  eos = hydro
  [../]
  
  [./YMomDissip]
    type = ArtificialDissipativeFlux
    variable = hv
    equ_name = y_mom
  [../]
[]

[AuxVariables]
  [./kappa_max_aux]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
  [./kappa_max_ak]
    type = MaterialRealAux
    variable = kappa_max_aux
    property = kappa_max
  [../]
[]

[Materials]
  [./EntropyViscosityCoeff]
    type = EntropyViscosityCoefficient
    block = 1
    h = h
    hu = hu
    hv = hv    
    eos = hydro
  [../]
[]

[BCs]
  [./bc_h]
    type = SolidWallBC
    variable = h
    boundary = '1 2 3'
    equ_name = continuity
    h = h
    hu = hu
    hv = hv
    eos = hydro
  [../]

  [./bc_hu]
    type = SolidWallBC
    variable = hu
    boundary = '1 2 3'
    equ_name = x_mom
    h = h
    hu = hu
    hv = hv
    eos = hydro
  [../]
  
  [./bc_hv]
    type = SolidWallBC
    variable = hv
    boundary = '1 2 3'
    equ_name = y_mom
    h = h
    hu = hu
    hv = hv
    eos = hydro
  [../]
[]

[Preconditioning]
  [./FDP]
    type = SMP # FDP
    full = true
    solve_type = 'PJFNK'
  [../]
[]

[Executioner]
  type = Transient
  scheme = bdf2
  
  dt = 1.e-1

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-6
  nl_max_its = 30

  end_time = 50.
#  num_steps = 100
[]

  [./Adaptivity]
    refine_fraction = 0.5
    coarsen_fraction = 0.05
    max_h_level = 2
    error_estimator = PatchRecoveryErrorEstimator
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  print_linear_residuals = false
  print_perf_log = true
[]
