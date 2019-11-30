#ifndef AI_H
#define AI_H

#include "Constants.h"
#include "Movement.h"
#include "LegalMoveChecker.h"
#include "FileIO.h"
#include "Conversion.h"
#include "Conditionals.h"
void CopyBoard(PieceData New[8][8], PieceData Old[8][8]);
void AIMove(char color, int level,int hint);


#endif

