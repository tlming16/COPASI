# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/libs/COPASIUI/COPASIUI.pro,v $
#   $Revision: 1.18 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2008/09/30 19:49:53 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# Automatically generated by qmake (1.07a) Fri Oct 27 13:32:17 2006
######################################################################

TEMPLATE = lib

SRC_TARGET = COPASIUI

include(../../common.pri)

CONFIG += qt

contains(DEFINES, HAVE_MML) {
  COPASI_LIBS += mml
}

contains(DEFINES, WITH_QWT3D) {
  COPASI_LIBS += barChart
}

COPASI_LIBS += layoutUI
COPASI_LIBS += MIRIAMUI
COPASI_LIBS += plotUI
COPASI_LIBS += tex
COPASI_LIBS += UI
COPASI_LIBS += wizard

include(../lib.pri)
