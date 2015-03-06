[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 50
  ny = 50
  xmin = 0.
  xmax = 1.
  ymin = 0.
  ymax = 1.
[]

[Functions]
  [./topology]
    type = VariableDepthRiverbed2D
    xmin = 0.4
    xmax = 0.6
    ymin = 0.4
    ymax = 0.6
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
      type = ConstantIC
      value = 1.
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
  b = b_aux
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
  b = b_aux
  eos = hydro
  [../]
  
  [./YMomDissip]
    type = ArtificialDissipativeFlux
    variable = hv
    equ_name = y_mom
  [../]
[]

[AuxVariables]
  [./b_aux]
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
  [./b_ak]
    type = FunctionAux
    variable = b_aux
    function = topology
  [../]

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
    block = 0
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
  [./bc_h_left]
    type = DirichletBC
    variable = h
    boundary = '3'
    value = 2.
  [../]

  [./bc_h]
    type = SolidWallBC
    variable = h
    boundary = '0 1 2'
    equ_name = continuity
    h = h
    hu = hu
    hv = hv
    eos = hydro
  [../]

  [./bc_hu_left]
    type = DirichletBC
    variable = hu
    boundary = '3'
    value = 0.
  [../]

  [./bc_hu]
    type = SolidWallBC
    variable = hu
    boundary = '0 1 2'
    equ_name = x_mom
    h = h
    hu = hu
    hv = hv
    eos = hydro
  [../]

  [./bc_hv_left]
    type = DirichletBC
    variable = hv
    boundary = '3'
    value = 0.
  [../]

  [./bc_hv]
    type = SolidWallBC
    variable = hv
    boundary = '0 1 2'
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
    time_dt = '1.e-2  1.e-2'
  [../]

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-8
  nl_max_its = 30

  end_time = 10.
  num_steps = 100

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
