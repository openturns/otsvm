
ot_add_current_dir_to_include_dirs ()
ot_add_source_file (svm.cpp)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set_source_files_properties (svm.cpp PROPERTIES COMPILE_FLAGS "-Wno-error=maybe-uninitialized")
endif ()
