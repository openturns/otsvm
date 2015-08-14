// SWIG file LibSVMDriverImplementation.i
// Author : $LastChangedBy: schueller $
// Date : $LastChangedDate: 2007-05-10 16:43:31 +0200 (Thu, 10 May 2007) $
// Id : $Id: LibSVMDriverImplementation.i 434 2007-05-10 14:43:31Z dutka $

%{
#include "SVMRegressionImplementation.hxx"
%}
 
%template(SVMRegressionImplementationdInterfaceObject)         OT::TypedInterfaceObject<OTSVM::SVMRegressionImplementation>;

%include SVMRegressionImplementation.hxx
namespace OTSVM { %extend SVMRegressionImplementation { SVMRegressionImplementation(const SVMRegressionImplementation & other) { return new OTSVM::SVMRegressionImplementation(other); } } }
