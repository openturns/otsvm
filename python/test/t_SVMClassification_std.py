#! /usr/bin/env python

import openturns as ot
import otsvm
import os

# we retrieve the sample from the file sample.csv
path = os.path.abspath(os.path.dirname(__file__))
dataInOut = ot.Sample().ImportFromCSVFile(path + '/sample.csv', ',')

dataIn = ot.Sample(861, 2)
dataOut = ot.Indices(861, 0)

# we build the input Sample and the output Sample because we must separate
# dataInOut
for i in range(861):
    a = dataInOut[i]
    b = ot.Point(2)
    b[0] = a[1]
    b[1] = a[2]
    dataIn[i] = b
    dataOut[i] = int(a[0])

# list of C parameter
cp = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]
# list of gamma parameter in kernel function
gamma = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]

# create the Problem
algo = otsvm.LibSVMClassification(dataIn, dataOut)
algo.setKernelType(otsvm.LibSVM.NormalRbf)
algo.setTradeoffFactor(cp)
algo.setKernelParameter(gamma)

# compute the classification
algo.run()
print('#######################')
print('Results with Samples I/O')
print('Accuracy(p.c.)=', algo.getAccuracy())
