#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################


BMPTK := $(BMPTK)../
# source files in this project (main.cpp is automatically assumed)
SOURCES := startup_sam3xa.c matrix.cpp Image.cpp String.cpp AnimatedImage.cpp Timer.cpp Obstacles.cpp straightLine.cpp Runner.cpp

# header files in this project
HEADERS := init.c

# other places to look for files for this project
SEARCH  := $(BMPTK)bmptk/targets/cortex/atmel/sam3xa/include core/

# set BMPTK to the next higher directory and defer to the Makefile.due
include $(BMPTK)Makefile.due
