//                                               -*- C++ -*-
/**
 *  @brief The test file for NormalRBF class.
 *
 *  Copyright 2014-2024 Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 */

#include <openturns/OT.hxx>
#include <openturns/OTtestcode.hxx>
#include <openturns/OStream.hxx>
#include "otsvm/OTSVM.hxx"

using namespace OT;
using namespace OT::Test;
using namespace OTSVM;


int main(void)
{
  TESTPREAMBLE;
  OStream fullprint(std::cout);
  try
  {
    //instantiate a Gaussian kernel with sigma = 2
    Collection<SVMKernel> kernels;
    kernels.add(NormalRBF(2.0));
    kernels.add(ExponentialRBF(2.0));
    kernels.add(LinearKernel());
    kernels.add(PolynomialKernel(3.0, 2.0, 1.0));
    kernels.add(RationalKernel(2.0));
    kernels.add(SigmoidKernel(1.0, 0.0));

    Sample X(0, 2);
    Sample Y(0, 2);
    X.add(Point({2.0, 2.0}));
    Y.add(Point({1.0, 1.0}));
    X.add(Point({0.0, 5.0}));
    Y.add(Point({0.0, 3.0}));

    for (UnsignedInteger i = 0; i < kernels.getSize(); ++ i)
    {
      const SVMKernel kernel(kernels[i]);
      for (UnsignedInteger j = 0; j < X.getSize(); ++ j)
      {
        const Point x(X[j]);
        const Point y(Y[j]);

        fullprint << " kernel (x,y) = " << kernel(x, y) << std::endl;
        fullprint << " dkernel/dx_i(x,y) = " << kernel.partialGradient(x, y) << std::endl;
        fullprint << " d2kernel/(dx_i*dx_j)(x,y) = " << kernel.partialHessian(x, y) << std::endl;
      }
    }
  }
  catch (TestFailed & ex)
  {
    std::cerr << ex << std::endl;
    return ExitCode::Error;
  }

  return ExitCode::Success;

}
