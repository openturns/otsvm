// SWIG file SVMKernel.i
// @author schueller
// @date   2012-01-02 11:44:01 +0100 (Mon, 02 Jan 2012)
// Id      SVMKernel.i 2287 2012-01-02 10:44:01Z schueller

%{
#include "SVMKernel.hxx"

namespace OT { 

  template <>
  struct traitsPythonType<OTSVM::SVMKernel>
  {
    typedef _PyObject_ Type;
  };


  template <>
  inline
  OTSVM::SVMKernel
  convert<_PyObject_,OTSVM::SVMKernel>(PyObject * pyObj)
  {
    void * ptr = 0;
    if (! SWIG_IsOK(SWIG_ConvertPtr( pyObj, &ptr, SWIG_TypeQuery("OTSVM::SVMKernelImplementation *"), 0 |  0 )))
      throw OT::InvalidArgumentException(HERE) << "Object passed as argument is not an object convertible to an SVMKernelImplementation";
    OTSVM::SVMKernelImplementation * p_ki = reinterpret_cast< OTSVM::SVMKernelImplementation * >( ptr );
    return *p_ki;
  }

} /* namespace OT */


%}

%template(SVMKernelImplementationTypedInterfaceObject)           OT::TypedInterfaceObject<OTSVM::SVMKernelImplementation>;

%typemap(in) const OTSVM::SVMKernel & {
  if (! SWIG_IsOK((SWIG_ConvertPtr($input, (void **) &$1, $1_descriptor, 0)))) {
    const OTSVM::SVMKernelImplementation * temp;
    if (! SWIG_IsOK(SWIG_ConvertPtr($input, (void **) &temp, SWIGTYPE_p_OTSVM__SVMKernelImplementation, 0))) {
      return NULL;
    }
    $1 = new OTSVM::SVMKernel( *temp );
  }
}

%typemap(typecheck,precedence=SWIG_TYPECHECK_POINTER) const OTSVM::SVMKernel & {
  const OTSVM::SVMKernelImplementation * temp;
  $1 = SWIG_IsOK(SWIG_ConvertPtr($input, NULL, $1_descriptor, 0)) || SWIG_IsOK(SWIG_ConvertPtr($input, (void **) &temp, SWIGTYPE_p_OTSVM__SVMKernelImplementation, 0));
}

%include SVMKernel.hxx
namespace OTSVM{  

%extend SVMKernel {

SVMKernel(const SVMKernel & other) { return new OTSVM::SVMKernel(other); }

}
}
