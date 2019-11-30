##########################################################################
# Makefile for BongCloudAI
# Authors: Yousef Althaqeb, Nicolas Chen, Hugh Fong, 
# 		Brandon H Lam, Quyen B To
#
#
# ########################################################################

COMPILE = gcc
OBJEFLAGS = -ansi -Wall -std=c99  -c -g -o3
SOURCES = .
OBJECTS = $(SOURCES)/AI.o $(SOURCES)/Movement.o $(SOURCES)/FileIO.o $(SOURCES)/Conversion.o $(SOURCES)/Main.o $(SOURCES)/LegalMoveChecker.o $(SOURCES)/Conditionals.o

#Default target
all: BongCloudAI

#TAR
tar: 
	tar -czvf Chess_Alpha_$(SOURCES).tar.gz /project/chess

###################### Clean-Up ###########################################

clean:
	rm -f $(SOURCES)/*.o BongCloudAI 

###################### Object Files #######################################
AI.o: $(SOURCES)/AI.c $(SOURCES)/Movement.h $(SOURCES)/Movement.c $(SOURCES)/Conditionals.h 
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/AI.c -o AI.o

Movement.o: $(SOURCES)/FileIO.h $(SOURCES)/FileIO.h $(SOURCES)/Movement.c $(SOURCES)/Conditionals.h
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/Movement.c -o Movement.o

Conditionals.o: $(SOURCES)/Conditionals.c $(SOURCES)/Conditionals.h $(SOURCES)/Conversion.h $(SOURCES)/Constants.h $(SOURCES)/LegalMoveChecker.h 
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/Conditionals.c -o Conditionals.o

FileIO.o: $(SOURCES)/FileIO.c $(SOURCES)/FileIO.h $(SOURCES)/Constants.h
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/FileIO.c -o FileIO.o

Main.o: $(SOURCES)/AI.h $(SOURCES)/AI.c $(SOURCES)/FileIO.h $(SOURCES)/FileIO.c $(SOURCES)/Main.c $(SOURCES)/Constants.h
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/Main.c -o Main.o

LegalMoveChecker.o:$(SOURCES)/LegalMoveChecker.c $(SOURCES)/LegalMoveChecker.h  $(SOURCES)/Constants.h
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/LegalMoveChecker.c -o LegalMoveChecker.o

Conversion.o: $(SOURCES)/Conversion.c $(SOURCES)/Conversion.h 
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/Conversion.c -o Conversion.o 

####################### Executable #######3################################

BongCloudAI: $(SOURCES)/AI.o $(SOURCES)/Movement.o $(SOURCES)/FileIO.o $(SOURCES)/Main.o $(SOURCES)/Conversion.o $(SOURCES)/LegalMoveChecker.o $(SOURCES)/Conditionals.o
	$(COMPILE) $(OBJECTS) -g -lm  -o chess
	#will be updated to build directly into bin folder later

####################### END OF FILE ######################################

