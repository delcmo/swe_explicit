[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
[]

[Variables]
  [./h]
    family = LAGRANGE
    order = first  
    [./InitialCondition]
      type = ConstantIC
      value = 2.
    [../]
  [../]
[]

[AuxVariables]
  [./hu]
    family = LAGRANGE
    order = first  
    [./InitialCondition]
      type = ConstantIC
      value = 10.
    [../]
  [../]
[]
 
[Kernels]
  [./Mass]
    type = TimeDerivative
    variable = h
    hu = hu
  [../]

  [./Mass]
    type = WaterHeightEqu
    variable = h
    hu = hu
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = h
    boundary = left
    value = 2.
  [../]

  [./right]
    type = DirichletBC
    variable = h
    boundary = right
    value = 2.
  [../]
[]

[Executioner]
  type = Transient
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
