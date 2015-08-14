#include <iostream>
#include <OT.hxx>
#include <math.h>
#include <LibSVMRegression.hxx>
#include <SVMRegressionImplementation.hxx>
#include <SVMRegression.hxx>
#include <NumericalPoint.hxx>
#include "OSS.hxx"
#include "OStream.hxx"
#include <SVMResourceMap.hxx>
#include "NumericalPoint.hxx"
#include "Description.hxx"
#include "NumericalMathFunction.hxx"
#include "Collection.hxx"
#include "ComposedDistribution.hxx"
#include "Distribution.hxx"
#include "EnumerateFunction.hxx"
#include "Indices.hxx"

using namespace OT;
using namespace OTSVM;


int main(int argc, char **argv)
{

  NumericalSample dataIn(100, 1);
  NumericalSample dataOut(100, 2);

  for(int i = 0; i < 100; i++)
  {
    NumericalPoint a(1);
    a[0] = i + 1;
    NumericalPoint b(2);
    b[0] = 2 * (i + 1);
    b[1] = i + 4;
    dataIn[i] = a;
    dataOut[i] = b;
  }


  NumericalPoint cp(2);
  cp[0] = 5;
  cp[1] = 10;

  NumericalPoint gamma(5);
  gamma[1] = 0.1;
  gamma[0] = 0.001;
  gamma[2] = 10;
  gamma[3] = 100;
  gamma[4] = 1;



  LibSVM::KernelType kernel = LibSVM::NormalRbf;
  OTSVM::LibSVMRegression regression(dataIn, dataOut, kernel);

  regression.setTradeoffFactor(cp);
  regression.setKernelParameter(gamma);
  regression.run();

  MetaModelResult result(regression.getResult());
  NumericalPoint residu(2);
  residu = result.getResiduals();
  NumericalPoint error(2);
  residu = result.getRelativeErrors();

  std::cout << std::setprecision(2) << result.getResiduals()[0] << " " << result.getResiduals()[1] << std::endl;
  std::cout << std::setprecision(2) << result.getRelativeErrors()[0] << " " << result.getRelativeErrors()[1] << std::endl;
}
