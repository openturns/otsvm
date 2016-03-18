// SWIG file LibSVM.i

%module otsvm
%feature("autodoc","1"); 

%pythoncode %{
# Override the default SWIG function
def _swig_repr(self):
  return self.str()   
%}


%{
#include <openturns/OT.hxx>
#include <openturns/PythonWrappingFunctions.hxx>
%}
 
// Prerequisites needed
%include typemaps.i
%include exception.i 
%ignore *::load(OT::Advocate & adv);
%ignore *::save(OT::Advocate & adv) const;

%import base_module.i
%import uncertainty_module.i

// The new classes
%include otsvm/OTSVMprivate.hxx
%include SVMKernelImplementation.i
%include SVMKernel.i
%include NormalRBF.i
%include ExponentialRBF.i
%include RationalKernel.i
%include PolynomialKernel.i
%include SigmoidKernel.i
%include LinearKernel.i
%include LibSVM.i
%include SVMRegressionImplementation.i
%include SVMRegression.i
%include LibSVMRegression.i
%include LibSVMClassification.i
%include KMeansClustering.i

%template(SVMKernelCollection) OT::Collection<OTSVM::SVMKernel>;



