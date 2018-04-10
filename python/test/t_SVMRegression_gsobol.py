#! /usr/bin/env python

from __future__ import print_function, division
from openturns import *
from otsvm import *


# Problem parameters
dimension = 3
# Create the Sobol function
# Reference analytical values
meanTh = 1.0
a = Point(dimension)
inputVariables = Description(dimension)
formula = Description(1)
formula[0] = "1.0"
covTh = 1.0
for i in range(dimension):
    a[i] = 0.5 * i
    covTh = covTh * (1.0 + 1.0 / (3.0 * (1.0 + a[i]) ** 2))
    inputVariables[i] = "xi" + str(i)
    formula[0] = formula[0] + \
        " * ((abs(4.0 * xi" + str(i) + " - 2.0) + " + \
        str(a[i]) + ") / (1.0 + " + str(a[i]) + "))"
covTh = covTh - 1.0
model = SymbolicFunction(inputVariables, formula)
RandomGenerator.SetSeed(0)
# Create the input distribution
marginals = [Uniform(0.0, 1.0)] * dimension
distribution = ComposedDistribution(marginals)

dataIn = distribution.getSample(250)
dataOut = model(dataIn)
# list of tradeOff parameter
cp = [5.0, 10.0, 100.0, 200.0, 500.0, 1000.0, 10000.0]
# list of gamma parameter in kernel function
gamma = [0.001, 0.01, 0.1, 0.5, 1, 5, 10, 20, 30, 40, 50, 100]
RandomGenerator.SetSeed(0)
# create the Problem
Regression = SVMRegression(dataIn, dataOut, LibSVM.NormalRbf)
Regression.setTradeoffFactor(cp)
Regression.setKernelParameter(gamma)
# compute the SVMRegression
Regression.run()
result = Regression.getResult()
residuals = result.getResiduals()
# Examine the results
print('#######################')
# print "residuals=%.4f" % residuals[0]
if residuals[0] <= 4.5e-3:
    print('OK')
else:
    print('FAIL')
relativeErrors = result.getRelativeErrors()
# print "relative errors=%.6f" % relativeErrors[0]
if relativeErrors[0] <= 8.0e-3:
    print('OK')
else:
    print('FAIL')
print('#######################')
print('')
