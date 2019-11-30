#ifndef CONSTANTS_H
#define CONSTANTS_H
typedef struct PD{
	int value;	/* Piece value, Pawn=1, Knights=3, Bishop=4, Rook =5, Queen 9, */
	char color;	/* w=White b=Black*/
	int BoardValue;
}PieceData;

typedef struct Undo{
	int value;	/* Piece value, Pawn=1, Knights=3, Bishop=4, Rook =5, Queen 9, */
	char color;	/* w=White b=Black*/
	int x0;
	int y0;
    int x1;
    int y1;
}UndoStructure;

UndoStructure UndoStruc[2];
PieceData Board[8][8];
#endif
