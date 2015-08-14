// SWIG file LibSVM.i
// Author : $LastChangedBy: schueller $
// Date : $LastChangedDate: 2008-08-28 17:36:47 +0200 (Thu, 28 Aug 2008) $
// Id : $Id: main.i 916 2008-08-28 15:36:47Z dutka $

%module otsvm
%feature("autodoc","1"); 

%pythoncode %{
# Override the default SWIG function
def _swig_repr(self):
  return self.str()   
%}


%{
#include "OT.hxx"
#include "PythonWrappingFunctions.hxx"
%}
 
// Prerequisites needed
%include typemaps.i
%include exception.i 
%ignore *::load(OT::Advocate & adv);
%ignore *::save(OT::Advocate & adv) const;

%import base_module.i
%import uncertainty_module.i

// The new classes
%include OTSVMprivate.hxx
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



