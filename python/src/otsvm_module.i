// SWIG file otsvm_module.i

%module (docstring="otsvm module") otsvm

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
%include LibSVMRegression.i
%include LibSVMClassification.i
%include KMeansClustering.i

%template(SVMKernelCollection) OT::Collection<OTSVM::SVMKernel>;



