[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 200
[]

[Functions]
  [./topology]
    type = VariableDepthRiverbed1D
    xmin = 0.4
    xmax = 0.6
  [../]

  [./ic_func]
    axis = 0
    type = PiecewiseLinear
    x = '0  0.1  0.1001  1'
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
    b = b_aux
    gravity = 9.8
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
  [./b_aux]
    family = LAGRANGE
    order = FIRST
  [../]
  
  [./u_aux]
    family = LAGRANGE
    order = FIRST
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
  
  [./u_ak]
    type = Xvelocity
    variable = u_aux
    h = h
    hu = hu
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
    eos = hydro
  [../]
[]

[BCs]
  [./left_h]
    type = SolidWallBC
    variable = h
    equ_name = continuity
    h = h
    hu = hu
    eos = hydro    
    boundary = left
  [../]

  [./right_h]
    type = SolidWallBC
    variable = h
    equ_name = continuity
    h = h
    hu = hu
    eos = hydro
    boundary = right
  [../]

  [./left_hu]
    type = SolidWallBC
    variable = hu
    equ_name = x_mom
    h = h
    hu = hu
    eos = hydro
    boundary = left
  [../]

  [./right_hu]
    type = SolidWallBC
    variable = hu
    equ_name = x_mom    
    h = h
    hu = hu
    eos = hydro
    boundary = right
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

  dt = 2.e-4

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-6
  nl_max_its = 10

  end_time = 0.2
#  num_steps = 10

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

#[Debug]
#  show_var_residual = 'h hu'
#  show_var_residual_norms = true
#[]