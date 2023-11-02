
if (NOT LIBSVM_FOUND)
  add_subdirectory (LibSVM)
  include_directories (${CMAKE_CURRENT_SOURCE_DIR}/LibSVM/otsvm)
endif ()

ot_add_current_dir_to_include_dirs ()

ot_add_source_file ( SVMKernel.cxx )
ot_add_source_file ( SVMKernelImplementation.cxx )
ot_add_source_file ( LinearKernel.cxx )
ot_add_source_file ( NormalRBF.cxx )
ot_add_source_file ( ExponentialRBF.cxx )
ot_add_source_file ( SigmoidKernel.cxx )
ot_add_source_file ( PolynomialKernel.cxx )
ot_add_source_file ( RationalKernel.cxx )
ot_add_source_file ( LibSVM.cxx )
ot_add_source_file ( SVMKernelRegressionEvaluation.cxx )
ot_add_source_file ( SVMKernelRegressionGradient.cxx )
ot_add_source_file ( SVMKernelRegressionHessian.cxx )
ot_add_source_file ( LibSVMRegression.cxx )
ot_add_source_file ( LibSVMClassification.cxx )
ot_add_source_file ( KMeansClustering.cxx )
ot_add_source_file ( SVMResourceMap.cxx )

ot_install_header_file ( SVMKernel.hxx )
ot_install_header_file ( SVMKernelImplementation.hxx )
ot_install_header_file ( LinearKernel.hxx )
ot_install_header_file ( NormalRBF.hxx )
ot_install_header_file ( ExponentialRBF.hxx )
ot_install_header_file ( SigmoidKernel.hxx )
ot_install_header_file ( PolynomialKernel.hxx )
ot_install_header_file ( RationalKernel.hxx )
ot_install_header_file ( LibSVM.hxx )
ot_install_header_file ( SVMKernelRegressionEvaluation.hxx )
ot_install_header_file ( SVMKernelRegressionGradient.hxx )
ot_install_header_file ( SVMKernelRegressionHessian.hxx )
ot_install_header_file ( LibSVMRegression.hxx )
ot_install_header_file ( LibSVMClassification.hxx )
ot_install_header_file ( KMeansClustering.hxx )
ot_install_header_file ( SVMResourceMap.hxx )


include_directories (${INTERNAL_INCLUDE_DIRS})

add_library (otsvm ${SOURCEFILES})
set_target_properties (otsvm PROPERTIES POSITION_INDEPENDENT_CODE ON)
if (BUILD_SHARED_LIBS)
  set_target_properties (otsvm PROPERTIES COMPILE_DEFINITIONS "OTSVM_DLL_EXPORTS")
endif ()

if ( NOT DEFINED LIB_VERSION ) 
  set ( LIB_VERSION 0.0.0 )
endif ()
if ( NOT DEFINED LIB_SOVERSION ) 
  set ( LIB_SOVERSION 0 )
endif ()
set_target_properties ( otsvm PROPERTIES VERSION ${LIB_VERSION} )
set_target_properties ( otsvm PROPERTIES SOVERSION ${LIB_SOVERSION} )
target_link_libraries (otsvm ${OPENTURNS_LIBRARY})

# Add targets to the build-tree export set
export (TARGETS otsvm FILE ${PROJECT_BINARY_DIR}/OTSVM-Targets.cmake)

# Install the export set for use with the install-tree
install(EXPORT OTSVM-Targets
        DESTINATION "${OTSVM_CONFIG_CMAKE_PATH}"
        COMPONENT Development)

install(TARGETS otsvm
        EXPORT  OTSVM-Targets 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION ${OTSVM_LIBRARY_PATH}
        ARCHIVE DESTINATION ${OTSVM_LIBRARY_PATH}
)

