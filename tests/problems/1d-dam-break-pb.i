[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 200
[]

[Functions]
  [./topology]
    type = ConstantFunction
    value = 0.
  [../]

  [./ic_func]
    axis = 0
    type = PiecewiseLinear
    x = '0  0.5  0.5001  1'
    y = '1  1    0.5     0.5'
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
  [../]

  [./Mass]
    type = WaterHeightEqu
    variable = h
    hu = hu
  [../]

  [./TimeMmom]
    type = TimeDerivative
    variable = hu
  [../]

  [./Momentum]
    type = MomentumEqu
    variable = hu
    h = h
    hu = hu
    component = 0
    eos = hydro
  [../]
  
  [./ArtDiffMass]
    type = ArtificialDissipativeFlux
    variable = h
    equ_name = continuity
  [../]
  
  [./ArtDiffMom]
    type = ArtificialDissipativeFlux
    variable = hu
    equ_name = x_mom
  [../]
[]

[AuxVariables]
  [./u_aux]
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
  [./u_ak]
    type = Xvelocity
    variable = u_aux
    h = h
    hu = hu
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
  [./LapidusViscosityCoeff]
    type = LapidusViscosityCoefficient
    block = 0
    h = h
    hu = hu
    u = u_aux
    eos = hydro
    Ce = 5.
  [../]
[]

[BCs]
  [./left_h]
    type = DirichletBC
    variable = h
    boundary = left
    value = 1.
  [../]

  [./right_h]
    type = DirichletBC
    variable = h
    boundary = right
    value = 0.5
  [../]

  [./left_hu]
    type = DirichletBC
    variable = hu
    boundary = left
    value = 0.
  [../]

  [./right_hu]
    type = DirichletBC
    variable = hu
    boundary = right
    value = 0.
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

  dt = 1.e-4

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-6
  nl_max_its = 10

#  end_time = 0.1
  num_steps = 10

[]

[Outputs]
  output_initial = true
  exodus = true
  print_linear_residuals = false
  print_perf_log = true
[]

#[Debug]
#  show_var_residual = 'h hu'
#  show_var_residual_norms = true
#[]