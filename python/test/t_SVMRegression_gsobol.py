#! /usr/bin/env python

import openturns as ot
import openturns.testing as ott
import otsvm

# Problem parameters
dimension = 3
# Create the Sobol function
# Reference analytical values
meanTh = 1.0
a = ot.Point(dimension)
inputVariables = ot.Description(dimension)
formula = ot.Description(1)
formula[0] = "1.0"
covTh = 1.0
for i in range(dimension):
    a[i] = 0.5 * i
    covTh = covTh * (1.0 + 1.0 / (3.0 * (1.0 + a[i]) ** 2))
    inputVariables[i] = "xi" + str(i)
    formula[0] = (
        formula[0]
        + " * ((abs(4.0 * xi"
        + str(i)
        + " - 2.0) + "
        + str(a[i])
        + ") / (1.0 + "
        + str(a[i])
        + "))"
    )
covTh = covTh - 1.0
model = ot.SymbolicFunction(inputVariables, formula)
ot.RandomGenerator.SetSeed(0)
# Create the input distribution
marginals = [ot.Uniform(0.0, 1.0)] * dimension
distribution = ot.ComposedDistribution(marginals)

dataIn = distribution.getSample(250)
dataOut = model(dataIn)
# list of tradeOff parameter
cp = [5.0, 10.0, 100.0, 200.0, 500.0, 1000.0, 10000.0]
# list of gamma parameter in kernel function
gamma = [0.001, 0.01, 0.1, 0.5, 1, 5, 10, 20, 30, 40, 50, 100]
ot.RandomGenerator.SetSeed(0)
# create the Problem
algo = otsvm.SVMRegression(dataIn, dataOut, otsvm.LibSVM.NormalRbf)
algo.setTradeoffFactor(cp)
algo.setKernelParameter(gamma)
# compute the SVMRegression
algo.run()
result = algo.getResult()
print(result)
validation = ot.MetaModelValidation(dataOut, result.getMetaModel()(dataIn))
mse = validation.computeMeanSquaredError()
ott.assert_almost_equal(mse, [0.0043475], 1.0, 1e-5)
