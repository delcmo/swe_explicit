[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmin = 0.
  xmax = 1.
  ymin = 0.
  ymax = 1.
[]

[Functions]
  [./topology]
    type = ConstantFunction
    value = 0.
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
      type = StepIC
      h_left=2.
      h_right=1.
      radius=0.1
      x_source=0.5
      y_source=0.5
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
    block = 0
    is_first_order = true
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
    type = DirichletBC
    variable = h
    boundary = 'left right top bottom'
    value = 1.
  [../]

  [./bc_hu]
    type = DirichletBC
    variable = hu
    boundary = 'left right top bottom'
    value = 0.
  [../]
  
  [./bc_hv]
    type = DirichletBC
    variable = hv
    boundary = 'left right top bottom'
    value = 0.
  [../]
[]

[Preconditioning]
  [./FDP]
    type = SMP
    full = true
    solve_type = 'NEWTON' # 'PJFNK'
#    petsc_options_iname = '-snes_type -snes_test_err'
#    petsc_options_value = 'test       1e-10'
  [../]
[]

[Executioner]
  type = Transient
  scheme = bdf2
  
  dt = 1.e-4

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-8
  nl_max_its = 30

  num_steps = 10

[]

[Outputs]
  output_initial = true
  exodus = true
  print_linear_residuals = false
  print_perf_log = true
[]
