[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 50
[]

[Functions]
  [./ic_func]
    axis = 0
    type = PiecewiseLinear
    x = '0  0.4  0.6  1'
    y = '2  2    4    4'
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
[]

[AuxVariables]
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
[]

[BCs]
  [./left]
    type = SaintVenantSetWaterHeightInletBC
    variable = h
    boundary = left
    equ_name = continuity
    hu = hu
    h_bc = 2.
    eos = hydro
  [../]

  [./right]
    type = SaintVenantSetWaterHeightOutletBC
    variable = h
    boundary = right
    equ_name = continuity
    h = h
    hu = hu
    h_bc = 4.
    eos = hydro
  [../]
[]

[Executioner]
  type = Transient
  scheme = bdf2
  solve_type = 'PJFNK'

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
