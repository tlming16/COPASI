# -*- coding: utf-8 -*-
# Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

import COPASI
import unittest
from types import *


class Test_CFunctionParameter(unittest.TestCase):
  def setUp(self):
    self.functions=COPASI.CRootContainer.getFunctionList()
    self.function=self.functions.findFunction("Iso Uni Uni")
    self.assert_(self.function!=None)
    self.assert_(self.function.__class__==COPASI.CFunction)
    self.parameters=self.function.getVariables()
    self.assert_(self.parameters!=None)
    self.assert_(self.parameters.__class__==COPASI.CFunctionParameters)
    index=self.parameters.findParameterByName("Keq",COPASI.CFunctionParameter.FLOAT64)
    self.parameter=self.parameters.getParameter(index)
    self.assert_(self.parameter!=None)
    self.assert_(self.parameter.__class__==COPASI.CFunctionParameter)

  def test_getKey(self):
    key=self.parameter.getKey()
    self.assert_(type(key)==StringType)

  def test_getType(self):
    b=self.parameter.getType()
    self.assert_(type(b)==IntType)
    self.assert_(b==COPASI.CFunctionParameter.FLOAT64)

  def test_setType(self):
    t=COPASI.CFunctionParameter.INT32
    self.parameter.setType(t)
    self.assert_(self.parameter.getType()==t)

  def test_getUsage(self):
    b=self.parameter.getUsage()
    self.assert_(type(b)==IntType)
    self.assert_(b==COPASI.CFunctionParameter.PARAMETER)

  def test_setUsage(self):
    t=COPASI.CFunctionParameter.VOLUME
    self.parameter.setUsage(t)
    self.assert_(self.parameter.getUsage()==t)




def suite():
  tests=[
          "test_getKey"        
         ,"test_getType"        
         ,"test_setType"        
         ,"test_getUsage"        
         ,"test_setUsage"        
        ]
  return unittest.TestSuite(map(Test_CFunctionParameter,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


