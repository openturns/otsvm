#! /usr/bin/env python

from openturns import *
from otsvm import *


# instantiate a kernel=Gaussian with sigma = 2
kernel = SigmoidKernel()
x = NumericalPoint(2, 2)
y = NumericalPoint(2, 1)

print(" kernel ([2 2],[1 1]) = %.3e " % kernel(x, y))
print(" dkernel/dx_i([2 2],[1 1]) = [ %.3e , %.3e ] " % (kernel.partialGradient(x, y)[0], kernel.partialGradient(x, y)[1]))
print(" d2kernel/(dx_i*dx_j)([2 2],[1 1]) =[ %.3e , %.3e , %.3e , %.3e ] " % (kernel.partialHessian(x, y)[0, 0], kernel.partialHessian(x, y)[0, 1], kernel.partialHessian(x, y)[1, 0], kernel.partialHessian(x, y)[1, 1],))

x[0] = 0
x[1] = 5
y[0] = 0
y[1] = 3

print(" kernel ([0 5],[0 3]) = %3.e" % kernel(x, y))
print(" dkernel/dx_i([0 5],[0 3]) [ %.3e , %.3e ] " % (kernel.partialGradient(x, y)[0], kernel.partialGradient(x, y)[1]))
print(" d2kernel/(dx_i*dx_j)([0 5],[0 3]) = [ %.3e , %.3e , %.3e , %.2e ] " % (kernel.partialHessian(x, y)[0, 0], kernel.partialHessian(x, y)[0, 1], kernel.partialHessian(x, y)[1, 0], kernel.partialHessian(x, y)[1, 1],))
