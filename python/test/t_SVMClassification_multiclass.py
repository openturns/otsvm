#! /usr/bin/env python

from __future__ import print_function
from openturns import *
from otsvm import *
import os

# we retreive the sample from the file sample.csv
path = os.path.abspath(os.path.dirname(__file__))
dataInOut = Sample.ImportFromCSVFile(path + '/multiclass.csv', ',')

dataIn = Sample(148, 4)
dataOut = Indices(148, 0)

# we build the input Sample and the output Sample because we must separate
# dataInOut
for i in range(148):
    a = dataInOut[i]
    b = Point(4)
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
Regression = LibSVMClassification(dataIn, dataOut)
Regression.setKernelType(LibSVM.NormalRbf)
Regression.setTradeoffFactor(cp)
Regression.setKernelParameter(gamma)

# compute the classification
Regression.run()
print('#######################')
print('Results with Samples I/O')
if Regression.getAccuracy() < 0.97:
    raise ValueError('acc<0.97')
# print('Accuracy(p.c.)= %.12g' % Regression.getAccuracy())

test = [0.0555554, -0.25, 0.118644, -4.03573e-08]
print(
    'We predict the class for the point [0.0555554,-0.25,0.118644,-4.03573e-08]: ', Regression.classify(test))
print('We grade the previous point for the 3 classes :')
print('class 1 :', Regression.grade(test, 1))
print('class 2: ', Regression.grade(test, 2))
print('class 3: ', Regression.grade(test, 3))
