
lib_LTLIBRARIES = libmmc.la


#libmmc.la
mmc_c = \
	utils.c \
	msg.c \
	stub.c \
	servant.c

mmc_h = mmc.h incl.h \
	utils.h \
	msg.h \
	stub.h \
	servant.h
     
libmmc_la_SOURCES = $(mmc_c) $(mmc_h)       
libmmc_la_CFLAGS = -Wall -I$(top_builddir) -I$(top_srcdir)
#libmm_la_LDFLAGS = -lm

#Headers
mmcincludedir = $(includedir)/mmc
mmcinclude_HEADERS = $(mmc_h)                
