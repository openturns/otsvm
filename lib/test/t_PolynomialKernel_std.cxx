//                                               -*- C++ -*-
/**
 *  @brief The test file for PolynomialKernel class.
 *
 *  Copyright 2014-2022 Phimeca
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

#include <openturns/OT.hxx>
#include <openturns/OTtestcode.hxx>
#include <openturns/OStream.hxx>
#include "otsvm/PolynomialKernel.hxx"


using namespace OT;
using namespace OT::Test;
using namespace OTSVM;

int main(void)
{
  TESTPREAMBLE;
  OStream fullprint(std::cout);
  try
  {
    PolynomialKernel kernel(3, 2, 1);
    Point x(2, 2);
    Point y(2, 1);

    fullprint << " kernel ([2 2],[1 1]) = " << kernel(x, y) << std::endl;
    fullprint << " dkernel/dx_i([2 2],[1 1]) = " << kernel.partialGradient(x, y) << std::endl;
    fullprint << " d2kernel/(dx_i*dx_j)([2 2],[1 1]) = " << kernel.partialHessian(x, y) << std::endl;;

    x[0] = 0;
    x[1] = 5;
    y[0] = 0;
    y[1] = 3;

    fullprint << " kernel ([0 5],[0 3]) = " << kernel(x, y) << std::endl;
    fullprint << " dkernel/dx_i([0 5],[0 3]) = " << kernel.partialGradient(x, y) << std::endl;
    fullprint << " d2kernel/(dx_i*dx_j)([0 5],[0 3]) = " << kernel.partialHessian(x, y) << std::endl;;

    PolynomialKernel kernel2(1, 2, 1);

    fullprint << " kernel2 ([0 5],[0 3]) = " << kernel2(x, y) << std::endl;
    fullprint << " dkernel2/dx_i([0 5],[0 3]) = " << kernel2.partialGradient(x, y) << std::endl;
    fullprint << " d2kernel2/(dx_i*dx_j)([0 5],[0 3]) = " << kernel2.partialHessian(x, y) << std::endl;;


  }
  catch (TestFailed & ex)
  {
    std::cerr << ex << std::endl;
    return ExitCode::Error;
  }

  return ExitCode::Success;

}
