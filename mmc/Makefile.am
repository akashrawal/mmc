
lib_LTLIBRARIES = libmmc.la


#libmmc.la
mmc_c = \
	msg.c

mmc_h = mmc.h incl.h \
	msg.h
     
libmmc_la_SOURCES = $(mmc_c) $(mmc_h)       
libmmc_la_CFLAGS = -Wall -I$(top_builddir) -I$(top_srcdir)
libmmc_la_LDFLAGS = $(MDSL_LIBS)

#Headers
mmcincludedir = $(includedir)/mmc
mmcinclude_HEADERS = $(mmc_h)                
