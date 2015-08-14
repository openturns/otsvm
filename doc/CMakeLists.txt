
find_package ( LATEX )
set ( IMAGEMAGICK_CONVERT convert )
set ( LATEX2HTML_CONVERTER latex2html )
include ( UseLATEX )

# latex part 
if ( PDFLATEX_COMPILER AND BIBTEX_COMPILER )

  if ( ${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    # in-source build
    set ( LATEX_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build )
#     execute_process (
#       COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/src/logoOpenTURNS.jpg ${CMAKE_CURRENT_SOURCE_DIR}/logoOpenTURNS.jpg
#     )  
  else ()
    # out-of-source build
    set ( LATEX_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )
  endif ()
  add_latex_document ( OTSVM_Documentation.tex
    INPUTS OTSVM_summary.tex OTSVM_UserManual.tex Math_Notations.sty OTSVM_ExamplesGuide.tex OTSVM_title.tex OTSVM_Documentation.sty OTSVM_ReferenceGuide.tex OTSVM_UseCasesGuide.tex
    IMAGES logoOTSVM.png
    DEFAULT_PDF
    MANGLE_TARGET_NAMES
  ) 

  configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/GenericInformation.tex.in 
                  ${CMAKE_CURRENT_BINARY_DIR}/GenericInformation.tex
                  @ONLY
  )
  
#   execute_process (
#     COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/latex2html/latex2html.sty ${LATEX_OUTPUT_PATH}/latex2html.sty
#     COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/src/Math_Notations.sty ${LATEX_OUTPUT_PATH}/Math_Notations.sty
#     COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/src/GenericInformation.tex ${LATEX_OUTPUT_PATH}/GenericInformation.tex
#   )     
  
  install ( FILES ${LATEX_OUTPUT_PATH}/OTSVM_Documentation.pdf DESTINATION share/doc/otsvm/pdf )

endif ()
