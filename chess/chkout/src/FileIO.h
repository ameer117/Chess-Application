#ifndef FileIO_H
#define FileIO_H
#include "Conversion.h"
void WriteLog(char *MoveFrom, char *MoveTo, int AiOrHuman);
void DeleteLog();
char *LastLog();
void UndoLog();
void SaveGame();
char *LoadGame();
PieceData ReturnPieceData(char *position);
#endif
