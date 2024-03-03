#
# Makefile.c
#

TARGET = all
C = gcc
CFLAGS = -std=c99 -Wall

#Version materielle
INCLDIRS =
LIBDIRS =

LIBS64 = -lm

SRCS = $(wildcard *.c)


OBJS = ${SRCS:.c=.o}

$(TARGET): $(OBJS)
	$(C) $(CFLAGS) $(INCLDIRS) -o $@ $(OBJS) $(LIBS64)

$(OBJS):
	$(C) $(CFLAGS) $(INCLDIRS) -c $*.c


clean:
	rm -f $(OBJS) core

veryclean: clean
	rm -f $(TARGET) a.out *.*~
	rm -rf $(TARGET).dSYM


# TARGET = all
# C = gcc
# CFLAGS = -std=c99 -Wall

# INCLDIRS =
# LIBDIRS =
# LIBS64 = -lm

# SRCS = $(wildcard *.c)
# OBJS = $(SRCS:.c=.o)

# $(TARGET): $(OBJS)
# 	$(C) $(CFLAGS) $(INCLDIRS) -o $@ $(OBJS) $(LIBS64)

# # Compilation de chaque fichier source individuellement
# Bmp2Matrix.o: Bmp2Matrix.c Bmp2Matrix.h
# 	$(C) $(CFLAGS) $(INCLDIRS) -c $< -o $@

# OuvertureFichiers.o: OuvertureFichiers.c OuvertureFichiers.h
# 	$(C) $(CFLAGS) $(INCLDIRS) -c $< -o $@

# Calculs.o: Calculs.c Calculs.h
# 	$(C) $(CFLAGS) $(INCLDIRS) -c $< -o $@

# main.o: main.c Bmp2Matrix.h OuvertureFichiers.h
# 	$(C) $(CFLAGS) $(INCLDIRS) -c $< -o $@

# clean:
# 	rm -f $(OBJS) core

# veryclean: clean
# 	rm -f $(TARGET) a.out *.*~
# 	rm -rf $(TARGET).dSYM
