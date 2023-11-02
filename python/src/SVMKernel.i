// SWIG file SVMKernel.i

%{
#include "otsvm/SVMKernel.hxx"

namespace OT {
  template <>
  struct traitsPythonType<OTSVM::SVMKernel>
  {
    typedef _PyObject_ Type;
  };


  template <>
  inline
  OTSVM::SVMKernel
  convert<_PyObject_, OTSVM::SVMKernel>(PyObject * pyObj)
  {
    void * ptr = 0;
    if (! SWIG_IsOK(SWIG_ConvertPtr( pyObj, &ptr, SWIG_TypeQuery("OTSVM::SVMKernelImplementation *"), 0 |  0 )))
      throw OT::InvalidArgumentException(HERE) << "Object passed as argument is not an object convertible to an SVMKernelImplementation";
    OTSVM::SVMKernelImplementation * p_ki = reinterpret_cast< OTSVM::SVMKernelImplementation * >( ptr );
    return *p_ki;
  }

} /* namespace OT */
%}

TypedInterfaceObjectImplementationHelper(OTSVM, SVMKernel, SVMKernelImplementation)

%copyctor OTSVM::SVMKernel;

%include otsvm/SVMKernel.hxx
