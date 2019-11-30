#ifndef CONVERSION_H
#define CONVERSION_H
#include "Constants.h"

void CopyBoard(PieceData New[8][8], PieceData Old[8][8]);
int ConvertInputX(char position[2]);
int ConvertInputY(char position[2]);
void ConvertXY(int x, int y,char *position);
int *ReturnData();
#endif
