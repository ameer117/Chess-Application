#include <stdio.h>
#include <stdlib.h>
#include "Movement.h"
#include "FileIO.h"

static char *detpiece(char piece[3], int i, int j);

void printboard(int BW)
{
    int count = 0;
    char piece[3] = {0};

    while( count<8 )
    {
       if(BW == 0)
       {
	if (count == 0)
        {printf("...........................................\n");}
        printf("  +----+----+----+----+----+----+----+----+\n");
        printf("%d | %2s ", (8-count), detpiece(piece, 0, (8-count-1)) );
        printf("| %2s ", detpiece(piece, 1, (8-count-1)) );
        printf("| %2s ", detpiece(piece, 2, (8-count-1)) );
        printf("| %2s ", detpiece(piece, 3, (8-count-1)) );
        printf("| %2s ", detpiece(piece, 4, (8-count-1)) );
        printf("| %2s ", detpiece(piece, 5, (8-count-1)) );
        printf("| %2s ", detpiece(piece, 6, (8-count-1)) );
        printf("| %2s |\n",  detpiece(piece, 7 ,(8-count-1)) );
         if (count == 7)
         {
            printf("  +----+----+----+----+----+----+----+----+\n");
            printf("     A    B    C    D    E    F    G    H\n");
            printf("...........\n");}
       }else if(BW == 1)
       {
	if (count == 0)
        {printf("...........................................\n");}
        printf("  +----+----+----+----+----+----+----+----+\n");
        printf("%d | %2s ", (count+1), detpiece(piece, 7, count) );
        printf("| %2s ", detpiece(piece, 6, count) );
        printf("| %2s ", detpiece(piece, 5, count) );
        printf("| %2s ", detpiece(piece, 4, count) );
        printf("| %2s ", detpiece(piece, 3, count) );
        printf("| %2s ", detpiece(piece, 2, count) );
        printf("| %2s ", detpiece(piece, 1, count) );
        printf("| %2s |\n",  detpiece(piece, 0 , count) );
        if (count == 7)
        {
            printf("  +----+----+----+----+----+----+----+----+\n");
            printf("     H    G    F    E    D    C    B    A\n");
            printf("...........\n");
        }
       }

        count++;
    }
}

static char *detpiece(char piece[3], int i, int j)
{
    char type = 0;
    char color = Board[i][j].color;

    /*switch( Board[i][j].color )
    {
        case "Black": color = b;
        case "White": color = w;
        default: color = 0;
    }*/

    switch( Board[i][j].value )
    {
        case 1: type = 'P'; break;
        case 3: type = 'N'; break;
        case 4: type = 'B'; break;
        case 5: type = 'R'; break;
        case 9: type = 'Q'; break;
        case 50: type = 'K'; break;
        default: type = 0;
    }

    //char *piece = malloc(sizeof(char) * 3);
      piece[0] = color;
	piece[1]= type;
    if ( type+color == 0)
    {
      piece[0] = 32;
      piece[1] = 32;
    }

    return piece;
}


int movementfunction(char *beforemove, char *aftermove, int AIorHuman)
{
         int HAI;

         if(AIorHuman == 1 || AIorHuman == 2)
            HAI = 0;
         if(AIorHuman == 0)
            HAI = 1;

         int bxcoor=0; int bycoor=0;
         int axcoor=0; int aycoor=0;	//initialized to 0 so we dont get warnings


         bycoor = beforemove[1]-49;
         aycoor = aftermove[1]-49;

         switch( beforemove[0] )
         {
            case 'A': bxcoor = 0; break;
            case 'B': bxcoor = 1; break;
            case 'C': bxcoor = 2; break;
            case 'D': bxcoor = 3; break;
            case 'E': bxcoor = 4; break;
            case 'F': bxcoor = 5; break;
            case 'G': bxcoor = 6; break;
            case 'H': bxcoor = 7; break;
            default: printf("Before move invalid");
         }
         switch( aftermove[0] )
         {
            case 'A': axcoor = 0; break;
            case 'B': axcoor = 1; break;
            case 'C': axcoor = 2; break;
            case 'D': axcoor = 3; break;
            case 'E': axcoor = 4; break;
            case 'F': axcoor = 5; break;
            case 'G': axcoor = 6; break;
            case 'H': axcoor = 7; break;
            default: printf("After move invalid");
         }

            UndoStruc[HAI].x0 = bxcoor;
            UndoStruc[HAI].y0 = bycoor;
            UndoStruc[HAI].x1 = axcoor;
            UndoStruc[HAI].y1 = aycoor;
            UndoStruc[HAI].color = Board[axcoor][aycoor].color;
            UndoStruc[HAI].value = Board[axcoor][aycoor].value;


            Board[axcoor][aycoor].color = Board[bxcoor][bycoor].color;
            Board[axcoor][aycoor].value = Board[bxcoor][bycoor].value;

            Board[bxcoor][bycoor].color = ' ';
            Board[bxcoor][bycoor].value = 0;

    return 0;
}

void AIMovement(int *move, PieceData *TempBoard)
{
	int x0=move[0];
	int y0=move[1];
	int x1=move[2];
	int y1=move[3];

            TempBoard[x1+8*y1].color = TempBoard[x0+8*y0].color;
            TempBoard[x1+8*y1].value = TempBoard[x0+8*y0].value;

            TempBoard[x0+8*y0].color = ' ';
            TempBoard[x0+8*y0].value = 0;

}

void LegalMovement(int *move, PieceData TempBoard[8][8])
{
	int x0=move[0];
	int y0=move[1];
	int x1=move[2];
	int y1=move[3];
//	int enPassant=move[5];
	int *LastMoveData = ReturnData();

            TempBoard[x1][y1].color = TempBoard[x0][y0].color;
            TempBoard[x1][y1].value = TempBoard[x0][y0].value;

            TempBoard[x0][y0].color = ' ';
            TempBoard[x0][y0].value = 0;
/*		
	    if(enPassant == 1){
		Board[LastMoveData[2]][LastMoveData[3]].value = 0;
		Board[LastMoveData[2]][LastMoveData[3]].color =' ';
		enPassant=0;
	    }*/
	free(LastMoveData);
}

void Undo(int mode)
{
    if(mode == 2)
    {
    Board[UndoStruc[1].x0][UndoStruc[1].y0].color = Board[UndoStruc[1].x1][UndoStruc[1].y1].color;
    Board[UndoStruc[1].x0][UndoStruc[1].y0].value = Board[UndoStruc[1].x1][UndoStruc[1].y1].value;

    Board[UndoStruc[1].x1][UndoStruc[1].y1].color = UndoStruc[1].color;
    Board[UndoStruc[1].x1][UndoStruc[1].y1].value = UndoStruc[1].value;
    }

    Board[UndoStruc[0].x0][UndoStruc[0].y0].color = Board[UndoStruc[0].x1][UndoStruc[0].y1].color;
    Board[UndoStruc[0].x0][UndoStruc[0].y0].value = Board[UndoStruc[0].x1][UndoStruc[0].y1].value;

    Board[UndoStruc[0].x1][UndoStruc[0].y1].color = UndoStruc[0].color;
    Board[UndoStruc[0].x1][UndoStruc[0].y1].value = UndoStruc[0].value;

}
