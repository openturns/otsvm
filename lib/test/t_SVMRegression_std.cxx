//                                               -*- C++ -*-
/**
 *  @brief The test file for SVMRegression class.
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
#include <otsvm/OTSVM.hxx>
#include <openturns/Function.hxx>
#include <openturns/ComposedDistribution.hxx>

using namespace OT;
using namespace OT::Test;
using namespace OTSVM;


int main(int /*argc*/, char ** /*argv*/)
{

  Sample dataIn(100, 1);
  Sample dataOut(100, 2);

  for(int i = 0; i < 100; i++)
  {
    dataIn(i, 0) = i + 1.0;
    dataOut[i] = Point({2.0 * (i + 1.0), i + 4.0});
  }


  const Point cp = {5.0, 10.0};
  const Point gamma = {0.001, 0.1, 10.0, 100.0, 1.0};

  LibSVM::KernelType kernel = LibSVM::NormalRbf;
  OTSVM::SVMRegression regression(dataIn, dataOut, kernel);

  regression.setTradeoffFactor(cp);
  regression.setKernelParameter(gamma);
  regression.run();

  const MetaModelResult result(regression.getResult());
  std::cout << "result=" << result << std::endl;

  MetaModelValidation validation(dataOut, result.getMetaModel()(dataIn));
  const Point mse = validation.computeMeanSquaredError();
  assert_almost_equal(mse, {0.00383302, 0.000958254}, 1e-5, 2e-4);
}
