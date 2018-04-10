#! /usr/bin/env python

from __future__ import print_function
from openturns import *
from otsvm import *

# instantiate a kernel=Gaussian with sigma = 2
kernel = ExponentialRBF(2)
x = Point(2, 2.0)
y = Point(2, 1.0)

print(' kernel ([2 2],[1 1]) = %.12g' % kernel(x, y))
print(' dkernel/dx_i([2 2],[1 1]) = ', repr(kernel.partialGradient(x, y)))
print(' d2kernel/(dx_i*dx_j)([2 2],[1 1]) = ', repr(
    kernel.partialHessian(x, y)))

x[0] = 0.0
x[1] = 5.0
y[0] = 0.0
y[1] = 3.0

print(' kernel ([0 5],[0 3]) = %.12g' % kernel(x, y))
print(' dkernel/dx_i([0 5],[0 3]) = ', repr(kernel.partialGradient(x, y)))
print(' d2kernel/(dx_i*dx_j)([0 5],[0 3]) = ', repr(
    kernel.partialHessian(x, y)))
