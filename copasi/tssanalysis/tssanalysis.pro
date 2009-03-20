# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/tssanalysis.pro,v $
#   $Revision: 1.8.2.1.4.2 $
#   $Name:  $
#   $Author: ssahle $
#   $Date: 2009/03/20 15:28:49 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# $Revision: 1.8.2.1.4.2 $ $Author: ssahle $ $Date: 2009/03/20 15:28:49 $
######################################################################

LIB = tssanalysis

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CILDMMethod.h \
           CILDMModifiedMethod.h \
	         CTSSAMethod.h \
           CTSSAProblem.h \
           CTSSATask.h \
           CCSPMethod.h

SOURCES += CILDMMethod.cpp \
           CILDMModifiedMethod.cpp \
	         CTSSAMethod.cpp \
           CTSSAProblem.cpp \
           CTSSATask.cpp \
           CCSPMethod.cpp


DISTFILES += tssanalysis.vcproj
