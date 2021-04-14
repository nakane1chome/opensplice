# Set target context
PROC		 = armv7
OS		 = darwin
OS_REV		 = 14
SPECIAL		 = DEBUG

ifdef OSPL_OUTER_HOME
include $(OSPL_OUTER_HOME)/setup/armv7.darwin14_clang_cross-default.mak
else
include $(OSPL_HOME)/setup/armv7.darwin14_clang_cross-default.mak
endif

# Compiler flags
CFLAGS_OPT       = -O0 -fno-strict-aliasing
CFLAGS_DEBUG     = -g #-D_TYPECHECK_ -DE_DEBUG
JCFLAGS          = -g
ifeq "$(USE_ADDRESS_SANITIZER)" "yes"
CFLAGS_DEBUG    += -fsanitize=address
LDFLAGS         += -fsanitize=address
endif

# Csc compiler flags
CSFLAGS_DEBUG    = -define:DEBUG\;TRACE -debug+ -debug:full
