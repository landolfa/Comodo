#*******************************************************************************
# ALMA - Atacama Large Millimiter Array
# (c) UNSPECIFIED - FILL IN, 2009 
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
#
#  "@(#) $Id$"
#
# who                when       what
# ----------------  ----------  ----------------------------------------------
# COMODO                        Created.
# 

#*******************************************************************************
# This Makefile follows VLT Standards (see Makefile(5) for more).
#*******************************************************************************
# REMARKS
#    None
#------------------------------------------------------------------------
MODULE = prototype

#
# user definable C-compilation flags
#USER_CFLAGS = 

#
# additional include and library search paths
#USER_INC = 
USER_LIB =  -lACE \
            -lTAO \
            -lTAO_DsLogAdmin \
            -lTAO_CosNaming \
            -lTAO_IORTable \
            -lTAO_PortableServer \
            -lTAO_Svc_Utils \
            -lTAO_CosTrading \
            -lTAO_CosNotification \
            -lTAO_DynamicAny \
            -lTAO_IFR_Client \
            -lTAO_CosProperty \
            -lacsutil \
            -lcdb \
            -llogging \
            -lacscomponent \
            -lbaci \
            -lmaci \
            -lmaciClient \
            -lacserr \
            -lm \
            -lloki \
            -lACSErrTypeCommon
            
#
# MODULE CODE DESCRIPTION:
# ------------------------
# As a general rule:  public file are "cleaned" and "installed"  
#                     local (_L) are not "installed".

#
# C programs (public and local)
# -----------------------------
EXECUTABLES     =
EXECUTABLES_L   = 

#
# <brief description of xxxxx program>
xxxxx_OBJECTS   =	
xxxxx_LDFLAGS   =
xxxxx_LIBS      =

#
# Resolve here the dependencies of the generated stubs
# This cleans up all missing symbols when building stubs libraries
# ----------------------------------------------------------------
DeviceStubs_LIBS = prototypeCommonStubs
LampStubs_LIBS = prototypeCommonStubs DeviceStubs
MotorStubs_LIBS = prototypeCommonStubs DeviceStubs
Lamp2Stubs_LIBS = prototypeCommonStubs LampStubs DeviceStubs
FilterStubs_LIBS = prototypeCommonStubs MotorStubs DeviceStubs
CCDImagStubs_LIBS = prototypeCommonStubs DeviceStubs
Lamp1Stubs_LIBS = prototypeCommonStubs LampStubs DeviceStubs
CCDSpectroStubs_LIBS = prototypeCommonStubs DeviceStubs
ICSStubs_LIBS = prototypeCommonStubs SubsystemStubs
DCSStubs_LIBS = prototypeCommonStubs SubsystemStubs
SubsystemStubs_LIBS = prototypeCommonStubs
OSStubs_LIBS = prototypeCommonStubs

#
# special compilation flags for single c sources
#yyyyy_CFLAGS   = 

#
# Includes (.h) files (public only)
# ---------------------------------
INCLUDES        =

#
# Libraries (public and local)
# ----------------------------
LIBRARIES       =
LIBRARIES_L     =

#
# <brief description of lllll library>
lllll_OBJECTS   =

#
# Scripts (public and local)
# ----------------------------
SCRIPTS         =
SCRIPTS_L       =

#
# TCL scripts (public and local)
# ------------------------------
TCL_SCRIPTS     =
TCL_SCRIPTS_L   =

#
# Python stuff (public and local)
# ----------------------------
PY_SCRIPTS         =
PY_SCRIPTS_L       =

PY_MODULES         =
PY_MODULES_L       =

PY_PACKAGES        =
PY_PACKAGES_L      =
pppppp_MODULES	   =

#
# <brief description of tttttt tcl-script>
tttttt_OBJECTS  =
tttttt_TCLSH    = 
tttttt_LIBS     = 

#
# TCL libraries (public and local)
# ------------------------------
TCL_LIBRARIES   =
TCL_LIBRARIES_L =

#
# <brief description of tttlll library>
tttlll_OBJECTS  = 

#
# Configuration Database Files
# ----------------------------
CDB_SCHEMAS = 
CDB_SCHEMAS += DeviceImpl
CDB_SCHEMAS += DCSImpl
CDB_SCHEMAS += Lamp2Impl
CDB_SCHEMAS += CCDImagImpl
CDB_SCHEMAS += SubsystemImpl
CDB_SCHEMAS += Lamp1Impl
CDB_SCHEMAS += CCDSpectroImpl
CDB_SCHEMAS += MotorImpl
CDB_SCHEMAS += ICSImpl
CDB_SCHEMAS += OSImpl
CDB_SCHEMAS += LampImpl
CDB_SCHEMAS += FilterImpl

# 
# IDL Files and flags
# ----------------------------
IDL_FILES = prototypeCommon
IDL_FILES += Device
IDL_FILES += Lamp
IDL_FILES += Motor
IDL_FILES += Lamp2
IDL_FILES += Filter
IDL_FILES += CCDImag
IDL_FILES += Lamp1
IDL_FILES += CCDSpectro
IDL_FILES += ICS
IDL_FILES += DCS
IDL_FILES += Subsystem
IDL_FILES += OS

TAO_IDLFLAGS =
USER_IDL =

#
# Jarfiles for Components and their directories
#
#COMPONENTS_JARFILES = $(MODULE)
JARFILES = $(MODULE)
$(MODULE)_DIRS = alma/prototype
$(MODULE)_EXTRAS =  

#
# java sources in Jarfile on/off
DEBUG=on

#
# ACS XmlIdl generation on/off
#
XML_IDL= 

#
# Java Component Helper Classes generation on/off
#
COMPONENT_HELPERS=

#
# Java Entity Classes generation on/off
#
XSDBIND=

#
# Schema Config files for the above
#
XSDBIND_INCLUDE=

# man pages to be done
# --------------------
MANSECTIONS =
MAN1 =
MAN3 =
MAN5 =
MAN7 =
MAN8 =

#
# local man pages
# ---------------
MANl =

#
# ASCII file to be converted into Framemaker-MIF
# --------------------
ASCII_TO_MIF = 

#
# other files to be installed
#----------------------------
INSTALL_FILES = 

#
# list of all possible C-sources (used to create automatic dependencies)
# ------------------------------
CSOURCENAMES = \
	$(foreach exe, $(EXECUTABLES) $(EXECUTABLES_L), $($(exe)_OBJECTS)) \
	$(foreach rtos, $(RTAI_MODULES) , $($(rtos)_OBJECTS)) \
	$(foreach lib, $(LIBRARIES) $(LIBRARIES_L), $($(lib)_OBJECTS))

#
#>>>>> END OF standard rules

#
# INCLUDE STANDARDS
# -----------------

MAKEDIRTMP := $(shell searchFile include/acsMakefile)
ifneq ($(MAKEDIRTMP),\#error\#)
   MAKEDIR := $(MAKEDIRTMP)/include
   include $(MAKEDIR)/acsMakefile
endif

#
# TARGETS
# -------
all:	do_all
	@echo " . . . 'all' done" 

clean : clean_all 
	@echo " . . . clean done"

clean_dist : clean_all clean_dist_all 
	@echo " . . . clean_dist done"

man   : do_man 
	@echo " . . . man page(s) done"

install : install_all
	@echo " . . . installation done"


#___oOo___
