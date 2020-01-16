//                                               -*- C++ -*-
/**
 *  @brief The test file for LibSVMRegression class.
 *
 *  Copyright 2014-2020 Phimeca
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */
#include <OT.hxx>
#include <otsvm/LibSVMRegression.hxx>
#include <otsvm/SVMRegressionImplementation.hxx>
#include <otsvm/SVMRegression.hxx>
#include <Point.hxx>
#include "OSS.hxx"
#include <openturns/OStream.hxx>
#include <otsvm/SVMResourceMap.hxx>
#include "Function.hxx"
#include "ComposedDistribution.hxx"

using namespace OT;
using namespace OTSVM;


int main(int argc, char **argv)
{

  Sample dataIn(100, 1);
  Sample dataOut(100, 2);

  for(int i = 0; i < 100; i++)
  {
    Point a(1);
    a[0] = i + 1;
    Point b(2);
    b[0] = 2 * (i + 1);
    b[1] = i + 4;
    dataIn[i] = a;
    dataOut[i] = b;
  }


  Point cp(2);
  cp[0] = 5;
  cp[1] = 10;

  Point gamma(5);
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
  Point residu(2);
  residu = result.getResiduals();
  Point error(2);
  residu = result.getRelativeErrors();

  std::cout << std::setprecision(2) << result.getResiduals()[0] << " " << result.getResiduals()[1] << std::endl;
  std::cout << std::setprecision(2) << result.getRelativeErrors()[0] << " " << result.getRelativeErrors()[1] << std::endl;
}
