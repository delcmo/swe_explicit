[GlobalParams]
  implicit = false
[]

[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0.
  xmax = 100.
  nx = 400
[]

[Functions]
  [./ic_func]
    axis = 0
    type = PiecewiseLinear
    x = '0  50  50.1 100'
    y = '10 10  0.5  0.5'
  [../]
[]

[UserObjects]
  [./hydro]
    type = HydrostaticPressure
    gravity = 9.8
  [../]
  
  [./smooth]
  type = MaterialSmoothing
  variable = u_aux
  var_name = grad_u_aux
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
  [../]

  [./ArtDiffMass]
    type = ArtificialDissipativeFlux
    variable = h
    equ_name = continuity
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
    gravity = 9.8
    component = 0
    eos = hydro
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
  
  [./grad_u_aux]
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
  [./EntropyViscosityCoeff]
    type = LapidusViscosityCoefficient
    block = 0
    Ce = 4.
    h = h
    hu = hu
    u = u_aux    
    eos = hydro
  [../]
[]

[BCs]
  [./left_h]
    type = DirichletBC
    variable = h
    boundary = left
    value = 10.
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

[Postprocessors]
  [./dt]
    type = TimeStepCFL
    h = h
    hu = hu
    eos = hydro
    cfl = 0.1
    outputs = none
  [../]
[]

[Executioner]
  type = Transient
  scheme = 'rk-2'

  dt = 1.e-2
  
  [./TimeStepper]
    type = PostprocessorDT
    postprocessor = dt
    dt = 1.e-3
  [../]

  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-6
  nl_max_its = 10

  end_time = 4.
#  num_steps = 1

  [./Quadrature]
    type = GAUSS
    order = SECOND
  [../]

[]

[Outputs]
  output_initial = false
  exodus = true
  print_linear_residuals = false
  print_perf_log = true
[]