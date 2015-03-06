[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 50
[]

[Functions]
  [./topology]
    type = ConstantFunction
    value = 10.
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
      value = 4.
    [../]
  [../]

  [./hu]
    family = LAGRANGE
    order = first  
    [./InitialCondition]
    type = ConstantIC
    value = 2.
    [../]
  [../]
[]

[Kernels]
  [./Time]
    type = TimeDerivative
    variable = h
  [../]

  [./Mass]
    type = WaterHeightEqu
    variable = h
    hu = hu
  [../]

  [./Momentum]
  type = MomentumEqu
  variable = hu
  h = h
  hu = hu
  gravity = 9.8
  component = 0
  topology = topology
  eos = hydro
  [../]
[]

[BCs]
  [./left_h]
    type = DirichletBC
    variable = h
    boundary = left
    value = 4.
  [../]

  [./right_h]
    type = DirichletBC
    variable = h
    boundary = right
    value = 4.
  [../]

  [./left_hu]
    type = DirichletBC
    variable = hu
    boundary = left
    value = 2.
  [../]

  [./right_hu]
    type = DirichletBC
    variable = hu
    boundary = right
    value = 2.
  [../]
[]

[Preconditioning]
  [./FDP]
    type = FDP
    full = true
    solve_type = 'PJFNK'
  [../]
[]

[Executioner]
  type = Transient
  scheme = bdf2
  
  dt = 0.1

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-6
  nl_max_its = 30

  num_steps = 10

[]

[Outputs]
  output_initial = true
  exodus = true
  print_linear_residuals = true
  print_perf_log = true
[]
