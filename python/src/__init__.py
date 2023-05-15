"""
    otsvm --- An OpenTURNS module
    ===================================================

    Documentation is available online at http://www.openturns.org.

    Contents
    --------
    'otsvm' is python module for Open TURNS, which enables to realize support vector regression and classification with    Libsvm and to manipualte results with OpenTURNS.

    Classes
    --------
    LibSVMRegression                                The class that supports the regression.

"""

# flake8: noqa

# ensures swig type tables order & dll load
import openturns as _ot

from .otsvm import *

__version__ = "0.11"
