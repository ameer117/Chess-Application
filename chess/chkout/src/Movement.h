#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "Constants.h"

void printboard(int BW);

int movementfunction(char *beforemove, char *aftermove, int AIorHuman);

void LegalMovement(int *move, PieceData TempBoard[8][8]);

void Undo(int mode);

void AIMovement(int *move, PieceData *TempBoard);
#endif
