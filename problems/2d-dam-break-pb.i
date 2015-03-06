[Mesh]
  dim = 2
#  file=partial-dam-break-small.e
  file=partial-dam-break-line.e
  uniform_refine = 2
[]

[Functions]
  [./topology]
    type = ConstantFunction
    value = 0.
  [../]
  
  [./ic_func]
    axis = 0
    type = PiecewiseLinear
    x = '-700  -0.5   0.5  700'
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
  eos = hydro
  [../]
  
  [./YMomDissip]
    type = ArtificialDissipativeFlux
    variable = hv
    equ_name = y_mom
  [../]
[]

[AuxVariables]
  [./entropy_aux]
    family = LAGRANGE
    order = FIRST
  [../]

  [./F_aux]
    family = LAGRANGE
    order = FIRST
  [../]

  [./G_aux]
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
[]

[AuxKernels]
  [./entropy_ak]
    type = EnergySw
    variable = entropy_aux
    h = h
    hu = hu
    hv = hv
  [../]

  [./F_ak]
    type = EnergyFluxSw
    variable = F_aux
    momentum = hu
    h = h
    hu = hu
    hv = hv
  [../]

  [./G_ak]
    type = EnergyFluxSw
    variable = G_aux
    momentum = hv
    h = h
    hu = hu
    hv = hv    
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
[]

[Materials]
  [./EntropyViscosityCoeff]
    type = EntropyViscosityCoefficient
    block = 1
    h = h
    hu = hu
    hv = hv
    entropy = entropy_aux
    F = F_aux
    G = G_aux    
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
  
  dt = 1.e-2
  
  [./TimeStepper]
    type = FunctionDT
    time_t =  '0  0.1.'
    time_dt = '5.e-3  5.e-2'
  [../]

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-8
  nl_max_its = 30

  end_time = 10.
#  num_steps = 10

#  [./Adaptivity]
#    refine_fraction = 0.5
#    coarsen_fraction = 0.05
#    max_h_level = 4
#    error_estimator = PatchRecoveryErrorEstimator
#  [../]

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
[]
