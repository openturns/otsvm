#! /usr/bin/env python

import openturns as ot
import otsvm
import os

# we retrieve the sample from the file sample.csv
path = os.path.abspath(os.path.dirname(__file__))
dataInOut = ot.Sample.ImportFromCSVFile(path + '/multiclass.csv', ',')

dataIn = ot.Sample(148, 4)
dataOut = ot.Indices(148, 0)

# we build the input Sample and the output Sample because we must separate
# dataInOut
for i in range(148):
    a = dataInOut[i]
    b = ot.Point(4)
    b[0] = a[1]
    b[1] = a[2]
    b[2] = a[3]
    b[3] = a[4]
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
if algo.getAccuracy() < 0.97:
    raise ValueError('acc<0.97')
# print('Accuracy(p.c.)= %.12g' % algo.getAccuracy())

test = [0.0555554, -0.25, 0.118644, -4.03573e-08]
print(
    'We predict the class for the point [0.0555554,-0.25,0.118644,-4.03573e-08]: ', algo.classify(test))
print('We grade the previous point for the 3 classes :')
print('class 1 :', algo.grade(test, 1))
print('class 2: ', algo.grade(test, 2))
print('class 3: ', algo.grade(test, 3))
