
include ( ${SWIG_USE_FILE} )

include_directories ( ${OPENTURNS_SWIG_INCLUDE_DIRS} )
add_definitions( ${OPENTURNS_SWIG_DEFINITIONS} )
include_directories ( ${INTERNAL_INCLUDE_DIRS} )
include_directories ( ${PYTHON_INCLUDE_DIRS} )

macro ( ot_add_python_module MODULENAME SOURCEFILE )
  set_source_files_properties ( ${SOURCEFILE} PROPERTIES CPLUSPLUS ON )
  set_source_files_properties ( ${SOURCEFILE} PROPERTIES SWIG_MODULE_NAME ${MODULENAME} )
  ot_install_swig_file ( ${SOURCEFILE} )
  if ( ${ARGC} GREATER 2 )
    set ( SWIG_MODULE_${MODULENAME}_EXTRA_DEPS ${ARGN} )
  endif ()
    
  set ( swig_other_sources )
  foreach ( it ${ARGN} )
    if ( ${it} MATCHES ".*\\.i$" )
      ot_install_swig_file ( ${it} )
    else ()
      set ( swig_other_sources ${swig_other_sources} "${it}" )
    endif ()
  endforeach ()

  swig_add_module ( ${MODULENAME} python ${SOURCEFILE} ${swig_other_sources} )
  swig_link_libraries ( ${MODULENAME} otsvm )
  if ( LINK_PYTHON_LIBRARY )
    swig_link_libraries ( ${MODULENAME} ${PYTHON_LIBRARIES} )
  endif ()
  
  set_target_properties ( ${SWIG_MODULE_${MODULENAME}_REAL_NAME} PROPERTIES NO_SONAME ON )

  if ( MINGW )
    set_target_properties ( ${SWIG_MODULE_${MODULENAME}_REAL_NAME} PROPERTIES
                                                                   LINK_FLAGS "-shared ${CMAKE_EXE_LINKER_FLAGS}" )
  endif ()
  list ( APPEND PYTHON_MODULES ${MODULENAME} )
endmacro ( ot_add_python_module )



ot_add_python_module( otsvm otsvm_module.i
                      SVMKernelImplementation.i
                      SVMKernel.i
                      NormalRBF.i
                      ExponentialRBF.i
                      RationalKernel.i
                      PolynomialKernel.i
                      SigmoidKernel.i
                      LinearKernel.i
                      LibSVM.i
                      SVMRegressionImplementation.i
                      SVMRegression.i
                      LibSVMRegression.i
                      LibSVMClassification.i
                      KMeansClustering.i )


foreach ( module ${PYTHON_MODULES} )
  install ( FILES ${CMAKE_CURRENT_BINARY_DIR}/${module}.py
            DESTINATION ${OTSVM_PYTHON_MODULE_PATH}/${PACKAGE_NAME}
            )
  install ( TARGETS _${module}
            LIBRARY DESTINATION ${OTSVM_PYTHON_MODULE_PATH}/${PACKAGE_NAME}
          )
endforeach ( module )

install ( FILES __init__.py
          DESTINATION ${OTSVM_PYTHON_MODULE_PATH}/${PACKAGE_NAME}
        )

install ( FILES ${SWIGFILES}
          DESTINATION ${OTSVM_SWIG_INCLUDE_PATH}
        )


