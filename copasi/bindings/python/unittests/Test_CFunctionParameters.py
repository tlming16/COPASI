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


class Test_CFunctionParameters(unittest.TestCase):
  def setUp(self):
    self.functions=COPASI.CRootContainer.getFunctionList()
    self.function=self.functions.findFunction("Iso Uni Uni")
    self.assert_(self.function!=None)
    self.assert_(self.function.__class__==COPASI.CFunction)
    self.parameters=self.function.getVariables()
    self.assert_(self.parameters!=None)
    self.assert_(self.parameters.__class__==COPASI.CFunctionParameters)

  def test_add(self):
    n=self.parameters.size()
    self.assert_(self.parameters.add("test",COPASI.CFunctionParameter.FLOAT64,COPASI.CFunctionParameter.VOLUME))
    self.assert_(self.parameters.size()==n+1)


  def test_remove(self):
    n=self.parameters.size()
    self.assert_(self.parameters.add("test2",COPASI.CFunctionParameter.FLOAT64,COPASI.CFunctionParameter.VOLUME))
    self.assert_(self.parameters.size()==n+1)
    self.parameters.remove("test2")
    self.assert_(self.parameters.size()==n)
    self.parameters.remove("test")
    self.assert_(self.parameters.size()==n-1)


  def test_size(self):
    n=self.parameters.size()
    self.assert_(type(n)==IntType)
    self.assert_(n==7)

  def test_isVector(self):
    b=self.parameters.isVector(COPASI.CFunctionParameter.SUBSTRATE)
    self.assert_(type(b)==BooleanType)
    self.assert_(b==False)
    f=self.functions.findFunction("Mass action (reversible)")
    self.assert_(f!=None)
    self.assert_(f.__class__==COPASI.CFunction)
    p=f.getVariables()
    self.assert_(p!=None)
    self.assert_(p.__class__==COPASI.CFunctionParameters)
    b=p.isVector(COPASI.CFunctionParameter.SUBSTRATE)
    self.assert_(type(b)==BooleanType)
    self.assert_(b==True)


  def test_getParameterByUsage(self):
    p=self.parameters.getParameterByUsage(COPASI.CFunctionParameter.PARAMETER,1)
    self.assert_(p.__class__==COPASI.CFunctionParameter)
    self.assert_(p.getObjectName()=="Kms")

  def test_getNumberOfParametersByUsage(self):
    n=self.parameters.getNumberOfParametersByUsage(COPASI.CFunctionParameter.PARAMETER)
    self.assert_(type(n)==IntType)
    self.assert_(n==5)

  def test_findParameterByName(self):
    n=self.parameters.findParameterByName("Kms",COPASI.CFunctionParameter.FLOAT64)
    self.assert_(type(n)==IntType)
    self.assert_(n==2)


def suite():
  tests=[
          "test_size"
         ,"test_add"
         ,"test_remove"
         ,"test_isVector"
         ,"test_getParameterByUsage"
         ,"test_getNumberOfParametersByUsage"
         ,"test_findParameterByName"        
        ]
  return unittest.TestSuite(map(Test_CFunctionParameters,tests))

if(__name__ == '__main__'):
    unittest.TextTestRunner(verbosity=2).run(suite())


