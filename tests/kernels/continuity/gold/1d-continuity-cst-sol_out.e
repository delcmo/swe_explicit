CDF      
      
len_string     !   len_line   Q   four      	time_step          len_name   !   num_dim       	num_nodes         num_elem   
   
num_el_blk        num_node_sets         num_side_sets         num_el_in_blk1     
   num_nod_per_el1       num_side_ss1      num_side_ss2      num_nod_ns1       num_nod_ns2       num_nod_var       num_info  f         api_version       @�
=   version       @�
=   floating_point_word_size            	file_size               int64_status             title         1d-continuity-cst-sol_out.e    maximum_name_length                    
time_whole                            |X   	eb_status                             �   eb_prop1               name      ID              �   	ns_status         	                    �   ns_prop1      	         name      ID              �   	ss_status         
                    �   ss_prop1      
         name      ID              �   coordx                      X      �   coordy                      X      P   coordz                      X      �   eb_names                       $      	    ns_names      	                 D      	$   ss_names      
                 D      	h   
coor_names                         d      	�   node_num_map                    ,      
   connect1                  	elem_type         EDGE2         P      
<   elem_num_map                    (      
�   elem_ss1                          
�   side_ss1                          
�   elem_ss2                          
�   side_ss2                          
�   node_ns1                          
�   node_ns2                          
�   vals_nod_var1                          X      |`   vals_nod_var2                          X      |�   name_nod_var                       D      
�   info_records                      qH                                               ?�������?ə�����?�333333?ٙ�����?�      ?�333333?�ffffff?陙����?�������?�                                                                                                                                                                                                                          left                             right                              left                             right                                                                                                                                                             	   
                                                   	   	   
   
                              	   
         
         h                                hu                                 ####################@       @$      @$      @$      @$      @$      @$      @$   # Created by MOOSE #$      @$                                                    ####################                                                             ### Command Line Arguments ###                                                   -i                                                                               1d-continuity-cst-sol.i                                                                                                                                           ### Version Info ###                                                             Framework Information:                                                           MOOSE version:           git commit 6cff32b on 2015-02-10                        PETSc Version:           3.4.4                                                   Current Time:            Thu Feb 19 14:03:08 2015                                Executable Timestamp:    Thu Feb 19 12:00:59 2015                                                                                                                                                                                                  ### Input File ###                                                                                                                                                []                                                                                 block                          = INVALID                                         coord_type                     = XYZ                                             fe_cache                       = 0                                               kernel_coverage_check          = 1                                               name                           = 'MOOSE Problem'                                 rz_coord_axis                  = Y                                               type                           = FEProblem                                       use_legacy_uo_aux_computation  = INVALID                                         use_legacy_uo_initialization   = INVALID                                         element_order                  = AUTO                                            order                          = AUTO                                            side_order                     = AUTO                                            active_bcs                     = INVALID                                         active_kernels                 = INVALID                                         inactive_bcs                   = INVALID                                         inactive_kernels               = INVALID                                         start                          = 0                                               dimNearNullSpace               = 0                                               dimNullSpace                   = 0                                               error_on_jacobian_nonzero_reallocation = 0                                       long_name                      =                                                 solve                          = 1                                               use_nonlinear                  = 1                                             []                                                                                                                                                                [AuxVariables]                                                                                                                                                      [./hu]                                                                             block                        = INVALID                                           family                       = LAGRANGE                                          initial_condition            = 0                                                 order                        = FIRST                                             initial_from_file_timestep   = 2                                                 initial_from_file_var        = INVALID                                                                                                                            [./InitialCondition]                                                               type                       = ConstantIC                                          block                      = INVALID                                             boundary                   = INVALID                                             long_name                  = AuxVariables/hu/InitialCondition                    value                      = 10                                                  variable                   = hu                                                [../]                                                                          [../]                                                                          []                                                                                                                                                                [BCs]                                                                                                                                                               [./left]                                                                           boundary                     = left                                              type                         = DirichletBC                                       use_displaced_mesh           = 0                                                 variable                     = h                                                 long_name                    = BCs/left                                          seed                         = 0                                                 value                        = 2                                               [../]                                                                                                                                                             [./right]                                                                          boundary                     = right                                             type                         = DirichletBC                                       use_displaced_mesh           = 0                                                 variable                     = h                                                 long_name                    = BCs/right                                         seed                         = 0                                                 value                        = 2                                               [../]                                                                          []                                                                                                                                                                [Executioner]                                                                      type                           = Transient                                       l_abs_step_tol                 = -1                                              l_max_its                      = 10000                                           l_tol                          = 1e-05                                           line_search                    = default                                         nl_abs_step_tol                = 1e-50                                           nl_abs_tol                     = 1e-50                                           nl_max_funcs                   = 10000                                           nl_max_its                     = 50                                              nl_rel_step_tol                = 1e-50                                           nl_rel_tol                     = 1e-08                                           no_fe_reinit                   = 0                                               petsc_options                  = INVALID                                         petsc_options_iname            = '-pc_type -pc_hypre_type'                       petsc_options_value            = 'hypre boomeramg'                               solve_type                     = PJFNK                                           abort_on_solve_fail            = 0                                               dt                             = 1                                               dtmax                          = 1e+30                                           dtmin                          = 2e-14                                           end_time                       = 1e+30                                           long_name                      = Executioner                                     n_startup_steps                = 0                                               num_steps                      = 10                                              picard_abs_tol                 = 1e-50                                           picard_max_its                 = 1                                               picard_rel_tol                 = 1e-08                                           predictor_scale                = INVALID                                         reset_dt                       = 0                                               restart_file_base              =                                                 scheme                         = implicit-euler                                  splitting                      = INVALID                                         ss_check_tol                   = 1e-08                                           ss_tmin                        = 0                                               start_time                     = 0                                               time_period_ends               = INVALID                                         time_period_starts             = INVALID                                         time_periods                   = INVALID                                         timestep_tolerance             = 2e-14                                           trans_ss_check                 = 0                                               use_multiapp_dt                = 0                                               verbose                        = 0                                             []                                                                                                                                                                [Executioner]                                                                      _fe_problem                    = 0x7f8fc0860600                                []                                                                                                                                                                [Kernels]                                                                                                                                                           [./Mass]                                                                           type                         = SvMass                                            block                        = INVALID                                           diag_save_in                 = INVALID                                           hu                           = hu                                                hv                           = INVALID                                           long_name                    = Kernels/Mass                                      save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = h                                               [../]                                                                          []                                                                                                                                                                [Mesh]                                                                             displacements                  = INVALID                                         block_id                       = INVALID                                         block_name                     = INVALID                                         boundary_id                    = INVALID                                         boundary_name                  = INVALID                                         construct_side_list_from_node_list = 0                                           ghosted_boundaries             = INVALID                                         ghosted_boundaries_inflation   = INVALID                                         patch_size                     = 40                                              second_order                   = 0                                               type                           = GeneratedMesh                                   uniform_refine                 = 0                                               centroid_partitioner_direction = INVALID                                         dim                            = 1                                               distribution                   = DEFAULT                                         elem_type                      = INVALID                                         long_name                      = Mesh                                            nemesis                        = 0                                               nx                             = 10                                              ny                             = 1                                               nz                             = 1                                               partitioner                    = default                                         patch_update_strategy          = never                                           xmax                           = 1                                               xmin                           = 0                                               ymax                           = 1                                               ymin                           = 0                                               zmax                           = 1                                               zmin                           = 0                                             []                                                                                                                                                                [Outputs]                                                                          checkpoint                     = 0                                               color                          = 1                                               console                        = 1                                               csv                            = 0                                               dofmap                         = 0                                               exodus                         = 1                                               file_base                      = INVALID                                         gmv                            = 0                                               gnuplot                        = 0                                               hide                           = INVALID                                         interval                       = 1                                               nemesis                        = 0                                               output_final                   = 0                                               output_if_base_contains        = INVALID                                         output_initial                 = 1                                               output_intermediate            = 1                                               output_on                      = 'INITIAL TIMESTEP_END'                          output_timestep_end            = 1                                               print_linear_residuals         = 1                                               print_perf_log                 = 1                                               show                           = INVALID                                         solution_history               = 0                                               sync_times                     =                                                 tecplot                        = 0                                               vtk                            = 0                                               xda                            = 0                                               xdr                            = 0                                                                                                                                [./console]                                                                        type                         = Console                                           additional_output_on         = INVALID                                           all_variable_norms           = 0                                                 append_displaced             = 0                                                 append_restart               = 0                                                 end_time                     = INVALID                                           file_base                    = INVALID                                           fit_mode                     = ENVIRONMENT                                       hide                         = INVALID                                           interval                     = 1                                                 linear_residual_dt_divisor   = 1000                                              linear_residual_end_time     = INVALID                                           linear_residual_start_time   = INVALID                                           linear_residuals             = 0                                                 long_name                    = Outputs/console                                   max_rows                     = 15                                                nonlinear_residual_dt_divisor = 1000                                             nonlinear_residual_end_time  = INVALID                                           nonlinear_residual_start_time = INVALID                                          nonlinear_residuals          = 0                                                 outlier_multiplier           = '0.8 2'                                           outlier_variable_norms       = 1                                                 output_elemental_variables   = 1                                                 output_failed                = 0                                                 output_file                  = 0                                                 output_final                 = 0                                                 output_if_base_contains      =                                                   output_initial               = 1                                                 output_input                 = 1                                                 output_input_on              = INVALID                                           output_intermediate          = 1                                                 output_linear                = 0                                                 output_nodal_variables       = 1                                                 output_nonlinear             = 0                                                 output_on                    = 'FAILED NONLINEAR TIMESTEP_END'                   output_postprocessors        = 1                                                 output_postprocessors_on     = TIMESTEP_END                                      output_scalar_variables      = 1                                                 output_scalars_on            = TIMESTEP_END                                      output_screen                = 1                                                 output_system_information    = 1                                                 output_system_information_on = INITIAL                                           output_timestep_end          = 1                                                 output_vector_postprocessors = 1                                                 output_vector_postprocessors_on = TIMESTEP_END                                   padding                      = 4                                                 perf_header                  = INVALID                                           perf_log                     = 0                                                 scientific_time              = 0                                                 setup_log                    = INVALID                                           setup_log_early              = 0                                                 show                         = INVALID                                           show_multiapp_name           = 0                                                 show_output_on               = 0                                                 solve_log                    = INVALID                                           start_time                   = INVALID                                           sync_only                    = 0                                                 sync_times                   =                                                   time_precision               = INVALID                                           time_tolerance               = 1e-14                                             use_displaced                = 0                                                 verbose                      = 0                                               [../]                                                                                                                                                             [./exodus]                                                                         type                         = Exodus                                            additional_output_on         = INVALID                                           append_displaced             = 0                                                 append_oversample            = 0                                                 elemental_as_nodal           = 0                                                 end_time                     = INVALID                                           file                         = INVALID                                           file_base                    = INVALID                                           hide                         = INVALID                                           interval                     = 1                                                 linear_residual_dt_divisor   = 1000                                              linear_residual_end_time     = INVALID                                           linear_residual_start_time   = INVALID                                           linear_residuals             = 0                                                 long_name                    = Outputs/exodus                                    nonlinear_residual_dt_divisor = 1000                                             nonlinear_residual_end_time  = INVALID                                           nonlinear_residual_start_time = INVALID                                          nonlinear_residuals          = 0                                                 output_elemental_on          = INVALID                                           output_elemental_variables   = 1                                                 output_failed                = 0                                                 output_final                 = 0                                                 output_if_base_contains      =                                                   output_initial               = 1                                                 output_input                 = 1                                                 output_input_on              = INITIAL                                           output_intermediate          = 1                                                 output_linear                = 0                                                 output_material_properties   = 0                                                 output_nodal_on              = INVALID                                           output_nodal_variables       = 1                                                 output_nonlinear             = 0                                                 output_on                    = 'INITIAL TIMESTEP_END'                            output_postprocessors        = 1                                                 output_postprocessors_on     = INVALID                                           output_scalar_variables      = 1                                                 output_scalars_on            = INVALID                                           output_system_information    = 1                                                 output_timestep_end          = 1                                                 output_vector_postprocessors = 1                                                 oversample                   = 0                                                 padding                      = 3                                                 position                     = INVALID                                           refinements                  = 0                                                 scalar_as_nodal              = 0                                                 sequence                     = INVALID                                           show                         = INVALID                                           show_material_properties     = INVALID                                           start_time                   = INVALID                                           sync_only                    = 0                                                 sync_times                   =                                                   time_tolerance               = 1e-14                                             use_displaced                = 0                                               [../]                                                                          []                                                                                                                                                                [Variables]                                                                                                                                                         [./h]                                                                              block                        = INVALID                                           eigen                        = 0                                                 family                       = LAGRANGE                                          initial_condition            = 0                                                 order                        = FIRST                                             scaling                      = 1                                                 initial_from_file_timestep   = 2                                                 initial_from_file_var        = INVALID                                                                                                                            [./InitialCondition]                                                               type                       = ConstantIC                                          block                      = INVALID                                             boundary                   = INVALID                                             long_name                  = Variables/h/InitialCondition                        value                      = 2                                                   variable                   = h                                                 [../]                                                                          [../]                                                                          []                                                                                         @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      ?�      @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @       @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @      @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @      @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @      @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @      @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @      @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @       @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @"      @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @       @       @       @       @       @       @       @       @       @       @       @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      @$      