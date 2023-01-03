#! /usr/bin/env python

import os
import openturns as ot
import otsvm

model = ot.SymbolicFunction(['E', 'F', 'L', 'I'], ['F*L^3/(3*E*I)'])
dim = model.getInputDimension()

R = ot.IdentityMatrix(dim)
mean = [50., 1., 10., 5.]
distribution = ot.Normal(mean, [1.] * dim, R)


dataIn = distribution.getSample(250)
dataOut = model(dataIn)

algo = otsvm.LibSVMRegression(dataIn, dataOut, otsvm.LibSVM.NormalRbf)
algo.run()
result = algo.getResult()

metamodel = result.getMetaModel()

fileName = 'myStudy.xml'

if ot.PlatformInfo.HasFeature('libxml2'):
    # save
    myStudy = ot.Study()
    myStudy.setStorageManager(ot.XMLStorageManager(fileName))
    myStudy.add('metamodel', metamodel)
    myStudy.save()

    # load
    myStudy = ot.Study()
    myStudy.setStorageManager(ot.XMLStorageManager(fileName))
    myStudy.load()
    loadedMetamodel = ot.Function()
    myStudy.fillObject("metamodel", loadedMetamodel)

    os.remove(fileName)

    if metamodel(mean) == loadedMetamodel(mean):
        print('OK')
else:
    print('OK')
