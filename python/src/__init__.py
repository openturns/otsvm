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

import sys
if sys.platform.startswith('win'):
    # this ensures OT dll is loaded
    import openturns

from .otsvm import *

__version__ = '0.10'
