#! /usr/bin/env python

from __future__ import print_function, division
import os
from openturns import *
from otsvm import *

model = SymbolicFunction(['E', 'F', 'L', 'I'], ['F*L^3/(3*E*I)'])
dim = model.getInputDimension()

R = IdentityMatrix(dim)
mean = [50., 1., 10., 5.]
distribution = Normal(mean, [1.] * dim, R)


dataIn = distribution.getSample(250)
dataOut = model(dataIn)

algo = SVMRegression(dataIn, dataOut, LibSVM.NormalRbf)
algo.run()
result = algo.getResult()

metamodel = result.getMetaModel()

fileName = 'myStudy.xml'

if hasattr(openturns, 'XMLStorageManager'):
    # save
    myStudy = Study()
    myStudy.setStorageManager(XMLStorageManager(fileName))
    myStudy.add('metamodel', metamodel)
    myStudy.save()

    # load
    myStudy = Study()
    myStudy.setStorageManager(XMLStorageManager(fileName))
    myStudy.load()
    loadedMetamodel = Function()
    myStudy.fillObject("metamodel", loadedMetamodel)

    os.remove(fileName)

    if metamodel(mean) == loadedMetamodel(mean):
        print('OK')
else:
    print('OK')
