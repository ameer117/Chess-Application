#ifndef CONDITIONALS_H
#define CONDITIONALS_H

#include "Constants.h"
#include "Movement.h"
#include "Conversion.h"

void Promotion(int AI);
int CheckKing(PieceData tempBoard[8][8], char playerColor, int anotherX, int anotherY);
int Checkmate(PieceData tempBoard[8][8], char playerColor);

#endif
