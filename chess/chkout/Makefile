##########################################################################
# Makefile for BongCloudAI
# Authors: Yousef Althaqeb, Nicolas Chen, Hugh Fong, 
# 		Brandon H Lam, Quyen B To
#
#
# ########################################################################

COMPILE = gcc
OBJEFLAGS = -ansi -Wall -std=c99  -c
DEBUG = -g
SOURCES = src
OBJECTS = $(SOURCES)/AI.o $(SOURCES)/Movement.o $(SOURCES)/FileIO.o $(SOURCES)/Conversion.o $(SOURCES)/Main.o $(SOURCES)/LegalMoveChecker.o $(SOURCES)/Conditionals.o

#Default target
all: BongCloudAI
test: BongCloudAITest
###################### Clean-Up ###########################################
clean:
	rm -f $(SOURCES)/*.o bin/chess 
#########################Tar##############################################
tar:
	tar -xvzf Chess_V1.0_src.tar.gz
###################### Object Files #######################################
AI.o: $(SOURCES)/AI.c $(SOURCES)/Movement.h  $(SOURCES)/Constants.h $(SOURCES)/LegalMoveChecker.h $(SOURCES)/FileIO.h
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/AI.c -o $(SOURCES)/AI.o

Movement.o:$(SOURCES)/Movement.c $(SOURCES)/Movement.h $(SOURCES)/Constants.h $(SOURCES)/Conversion.h $(SOURCES)/FileIO.h
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/Movement.c -o $(SOURCES)/Movement.o

Conditionals.o: $(SOURCES)/Conditionals.c $(SOURCES)/Conditionals.h $(SOURCES)/Conversion.h $(SOURCES)/Constants.h $(SOURCES)/LegalMoveChecker.h 
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/Conditionals.c -o $(SOURCES)/Conditionals.o

FileIO.o: $(SOURCES)/FileIO.c $(SOURCES)/FileIO.h $(SOURCES)/Constants.h $(SOURCES)/Conversion.h
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/FileIO.c -o $(SOURCES)/FileIO.o

Main.o: $(SOURCES)/Main.c $(SOURCES)/FileIO.h $(SOURCES)/Constants.h $(SOURCES)/AI.h $(SOURCES)/Conditionals.h $(SOURCES)/Movement.h $(SOURCES)/LegalMoveChecker.h
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/Main.c -o $(SOURCES)/Main.o

LegalMoveChecker.o:$(SOURCES)/LegalMoveChecker.c $(SOURCES)/LegalMoveChecker.h  $(SOURCES)/Constants.h $(SOURCES)/Conversion.h $(SOURCES)/Conditionals.h
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/LegalMoveChecker.c -o $(SOURCES)/LegalMoveChecker.o

Conversion.o: $(SOURCES)/Conversion.c $(SOURCES)/Conversion.h $(SOURCES)/Constants.h
	$(COMPILE) $(OBJEFLAGS) $(SOURCES)/Conversion.c -o $(SOURCES)/Conversion.o 
############################Test###########################################
Test.o: $(SOURCES)/Constants.h $(SOURCES)/AI.h $(SOURCES)/Conditionals.h $(SOURCES)/Movement.h $(SOURCES)/LegalMoveChecker.h $(SOURCES)/test_rulecheck.c 
	$(COMPILE) $(OBJEFLAGS) $(DEBUG) $(SOURCES)/test_rulecheck.c -o $(SOURCES)/test_rulecheck.o
AI_Debug.o: $(SOURCES)/AI.c $(SOURCES)/Movement.h  $(SOURCES)/Constants.h $(SOURCES)/LegalMoveChecker.h $(SOURCES)/FileIO.h
	$(COMPILE) $(OBJEFLAGS) -DDEBUG $(SOURCES)/AI.c -o $(SOURCES)/AI_Debug.o
####################### Executable ########################################

BongCloudAI: AI.o Movement.o FileIO.o Main.o Conversion.o LegalMoveChecker.o Conditionals.o
	$(COMPILE) $(OBJECTS) -lm  -o bin/chess
###########################Test############################################
BongCloudAITest: AI_Debug.o Movement.o FileIO.o LegalMoveChecker.o Conditionals.o Conversion.o Test.o
	$(COMPILE)  $(SOURCES)/AI_Debug.o $(SOURCES)/Movement.o $(SOURCES)/FileIO.o $(SOURCES)/Conversion.o $(SOURCES)/test_rulecheck.o $(SOURCES)/LegalMoveChecker.o $(SOURCES)/Conditionals.o -lm -o bin/test
	bin/test
####################### END OF FILE #######################################

