#! /usr/bin/env python

from __future__ import print_function, division
from openturns import *
from otsvm import *
from math import *

# Problem parameters
dimension = 3
a = 7.0
b = 0.1
# Reference analytical values
meanTh = a / 2
covTh = (b ** 2 * pi ** 8) / 18.0 + \
    (b * pi ** 4) / 5.0 + (a ** 2) / 8.0 + 1.0 / 2.0
sob_1 = [(b * pi ** 4 / 5.0 + b ** 2 * pi ** 8 / 50.0 + 1.0 / 2.0)
         / covTh, (a ** 2 / 8.0) / covTh, 0.0]
sob_2 = [0.0, (b ** 2 * pi ** 8 / 18.0 - b ** 2 * pi ** 8 / 50.0) / covTh, 0.0]
sob_3 = [0.0]
sob_T1 = [sob_1[0] + sob_2[0] + sob_2[1] + sob_3[0], sob_1[1] + sob_2[0]
          + sob_2[2] + sob_3[0], sob_1[2] + sob_2[1] + sob_2[2] + sob_3[0]]
sob_T2 = [sob_2[0] + sob_2[1] + sob_3[0], sob_2[0]
          + sob_2[2] + sob_3[0], sob_2[1] + sob_2[2] + sob_3[0]]
sob_T3 = [sob_3[0]]
# Create the Ishigami function
inputVariables = ["xi1", "xi2", "xi3"]
formula = "sin(xi1) + (" + str(a) + \
    ") * (sin(xi2)) ^ 2 + (" + str(b) + ") * xi3^4 * sin(xi1)"
model = SymbolicFunction(inputVariables, [formula])

# Create the input distribution
marginals = [Uniform(-pi, pi)] * 3
distribution = ComposedDistribution(marginals)
dataIn = distribution.getSample(250)
dataOut = model(dataIn)

# Create the SVMRegression result
# list of tradeOff parameter
cp = [500.0, 200.0, 150.0, 100.0, 75.0, 50.0, 10.0]
# list of gamma parameter in kernel function
gamma = [0.0001, 0.001, 0.15, 0.25, 0.35, 0.4, 0.5, 0.6, 0.8, 1, 10, 100]

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
print('######################')
# print "residuals=%.4f" % residuals[0]
if residuals[0] <= 1.2e-3:
    print('OK')
else:
    print('FAIL')
relativeErrors = result.getRelativeErrors()
# print "relative errors=%.6f" % relativeErrors[0]
if relativeErrors[0] <= 2.4e-5:
    print('OK')
else:
    print('FAIL')
print('######################')
print('')
