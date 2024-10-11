"""
    otsvm
    =====

    Documentation is available online at http://www.openturns.org.

    Contents
    --------
    'otsvm' is python module for Open TURNS, which enables to perform support vector regression
    and classification using LibSVM and to manipulate results with OpenTURNS.

    Classes
    --------
    SVMRegression                                The class that supports the regression.

"""

# flake8: noqa

# ensures swig type tables order & dll load
import openturns as _ot

from .otsvm import *

__version__ = '0.15'
