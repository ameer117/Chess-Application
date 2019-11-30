//
// Created by Nicolas on 1/31/2018.
//
#include "Conditionals.h"
#include <stdio.h>
#include "Constants.h"
#include "LegalMoveChecker.h"
#include "Conversion.h"
#include <stdlib.h>
#include "Conditionals.h"
#include "FileIO.h"

static int PawnFlag(int xStart, int yStart, int xEnd, int yEnd, int *LastMoveData, int *enPassant,PieceData TempBoard[8][8],int AIorHuman);
static int RookFlag(int xStart, int yStart, int xEnd, int yEnd,PieceData TempBoard[8][8]);
static int BishopFlag(int xStart, int yStart, int xEnd, int yEnd,PieceData TempBoard[8][8]);
static int KnightFlag(int xStart, int yStart, int xEnd, int yEnd,PieceData TempBoard[8][8]);
static int QueenFlag(int xStart, int yStart, int xEnd, int yEnd,PieceData TempBoard[8][8]);
static int KingFlag(int xStart, int yStart, int xEnd, int yEnd);

int LegalMoveChecker(PieceData TempBoard[8][8],char start[2], char end[2], char ColorofPlayer, int AIorHuman){
    int xStart, yStart, xEnd, yEnd;
    int enPassant;
    int legal=0;
    if(start[0]>'H' || start[0] < 'A' || end[0] > 'H' || end[0] < 'A' || start[1]<'1'|| start[1] > '8' || end[1] < '1' || end[1] > '8'){	//check for invalid move
	    printf("Inputted is Incorrectly\n");
	    return 0;
    }

    xStart = ConvertInputX(start);
    yStart = ConvertInputY(start);
    xEnd = ConvertInputX(end);
    yEnd = ConvertInputY(end);

    int Data[4]={xStart,yStart,xEnd,yEnd};
    if(TempBoard[xStart][yStart].value==0){
	    return 0;
    }
    if(TempBoard[xStart][yStart].color != ColorofPlayer){	//if we are moving into space which is already occupied by our own space return 0. Always illegal
	    return 0;
    }
    if(TempBoard[xEnd][yEnd].color == ColorofPlayer){	//if we are moving into space which is already occupied by our own space return 0. Always illegal
	    return 0;
    }

    if(xStart == xEnd && yStart == yEnd)	//if we are trying to move to the same space we were in before, always illegal
    {
        return 0;
    }
    	int *LastMoveData;
	LastMoveData=ReturnData();
    switch (TempBoard[xStart][yStart].value) {
	case 0:/*trying to move empty piece */
	    return 0;
        case 1: /*The value of the piece is for a pawn*/
            legal = PawnFlag(xStart,yStart,xEnd,yEnd,LastMoveData,&enPassant,TempBoard,AIorHuman); /* Set that piece is a pawn*/
            break;
        case 3: /*The value of the piece is for a Knight*/
            legal = KnightFlag(xStart,yStart,xEnd,yEnd,TempBoard); /* Set that piece is Knight*/
            break;
        case 4: /*The value of the piece is for a Bishop*/
            legal = BishopFlag(xStart,yStart,xEnd,yEnd,TempBoard); /* Set that piece is Bishop*/
            break;
        case 5: /* The value of the piece is for a Rook*/
            legal = RookFlag(xStart,yStart,xEnd,yEnd,TempBoard); /* Set that piece is Rook*/
            break;
        case 9: /*The value of the piece is for a Queen*/
            legal = QueenFlag(xStart,yStart,xEnd,yEnd,TempBoard); /* Set that piece is Queen*/
            break;
        case 50: /*The value of the piece is for a King*/
            legal = KingFlag(xStart,yStart,xEnd,yEnd); /*Set that piece is King*/
            break;
    }
	
    	if(legal == 1){		//check if king will be in check after
    		PieceData TemporaryBoard[8][8];
		CopyBoard(TemporaryBoard,TempBoard);
		LegalMovement(Data,TemporaryBoard);
		if(CheckKing(TemporaryBoard,ColorofPlayer, -1, -1) == 1){	//if king is still in check in the board after doing the move, it is illegal
//			printf("CheckKing went wrong");
		//	printf("%s  ", start);
		//	printf("%s\n", end);
			return 0;
  		}
	}
	if(legal==1 && enPassant==1 && AIorHuman==0){	//if human checking then kill, if AI dont actually perform kill
		Board[LastMoveData[2]][LastMoveData[3]].value = 0;
		Board[LastMoveData[2]][LastMoveData[3]].color =' ';
		enPassant=0;
	}

free(LastMoveData);
return legal;    
}

static int PawnFlag(int xStart, int yStart, int xEnd, int yEnd,int *LastMoveData,int *enPassant,PieceData TempBoard[8][8],int AIorHuman){
	int i=0;
	int Moving = 0;
	int Attacking = 0;
	
	/* CASE WHITE */
	if(TempBoard[xStart][yStart].color == 'w'){
		if(yStart == 1 && yEnd == 3 && xStart==xEnd){	//user is trying to move first pawn two spaces
			for(i = 1; yStart + i<= yEnd; i++){
				if(TempBoard[xStart][yStart+i].value != 0){
					return 0;
				}
				if(yStart +i ==yEnd){
					return 1;
				}
			}
		}

		if((xStart == xEnd && yStart +1 == yEnd)){	//check if user is trying to move one space forward
			Moving = 1;
		}

		if((xStart + 1 == xEnd || xStart - 1 == xEnd) && yStart + 1 == yEnd){ //check if user is trying to move one square diagonally
			Attacking = 1;
		}
		
		if(Attacking != 1 && Moving != 1){ //return 0 if neither attacking nor moving
			return 0;
		}
		if(Moving==1){	//check if moving is valid
			if(TempBoard[xEnd][yEnd].value != 0){	//if space infront is occupied return illegal else return legal
				return 0;
			}else{
				return 1;
			}
		}
		if(Attacking == 1){
			if(xEnd == LastMoveData[0] && yEnd-1 == LastMoveData[3] && TempBoard[LastMoveData[2]][LastMoveData[3]].value == 1 && LastMoveData[1]== 2+LastMoveData[3]){
				*enPassant=1;
				if(AIorHuman==1){return 0;}
				else{return 1;}	//written as: if moving behind a piece that is a pawn, that just jumped two moves forwards in the last move
			}
			if(TempBoard[xEnd][yEnd].color == 'b'){
				return 1;	//return 1 if attacking black piece
			}else{
				return 0;	//if board is blank
			}
		}
	}
	
	/* END OF CASE WHITE */


	/* CASE BLACK */
        if(TempBoard[xStart][yStart].color == 'b'){
                if(yStart == 6 && yEnd == 4 && xStart==xEnd){   //user is trying to move first pawn two spaces
                        for(i = 1;  yStart - i >= yEnd; i++){
                                if(TempBoard[xStart][yStart-i].value != 0){
                                        return 0;
                                }
				if(yStart - i == yEnd){
                                        return 1;
                                }
                        }
                }   

                if((xStart == xEnd && yStart -1 == yEnd)){        //check if user is trying to move one space forward
                        Moving = 1;
                }   

                if((xStart + 1 == xEnd || xStart - 1 == xEnd) && yStart - 1 == yEnd){ //check if user is trying to move one square diagonally
                        Attacking = 1;
                }   
    
                if(Attacking != 1 && Moving != 1){ //return 0 if neither attacking nor moving
                        return 0;
                }   

                if(Moving==1){  //check if moving is valid
                        if(TempBoard[xEnd][yEnd].value != 0){     //if space infront is occupied return illegal else return legal
                                return 0;
                        }else{
                                return 1;
                        }   
                }   
                if(Attacking == 1){ 
			if(xEnd == LastMoveData[0] && yEnd+1 == LastMoveData[3] && TempBoard[LastMoveData[2]][LastMoveData[3]].value == 1 && LastMoveData[1] == LastMoveData[3]-2){
				*enPassant=1;
				if(AIorHuman==1){return 0;}
				else{return 1;}	//written as: if moving behind a piece that is a pawn, that just jumped two moves forwards in the last move
			}
                        if(TempBoard[xEnd][yEnd].color == 'w'){     //check if attacking space is the correct color
                                return 1;	//correct attack
                        }else{
                                return 0;	//empty
                        }   
                }   
        }
	/* END OF CASE BLACK */	
	printf("Pawn Error...Aborting...");
	exit(10);
	return -1;
}

static int KnightFlag(int xStart,int yStart,int xEnd,int yEnd,PieceData TempBoard[8][8]){
	//+2 +1
	if(xStart +2 <8 && xStart +2 >=0){
		if(yEnd +1 <8 && yEnd +1 >=0){
			if(xEnd == xStart +2  && yEnd == yStart +1){
				return 1;
			}				
		}
	}	
	
	//+2 -1
	if(xStart +2 <8 && xStart +2 >=0){
		if(yEnd -1 <8 && yEnd -1 >=0){
			if(xEnd == xStart +2 && yEnd == yStart -1){
				return 1;	
			}
		}
	}
	//+1 +2
	if(xStart +1 <8 && xStart +1 >=0){
		if(yStart +2 <8 && yStart +2 >=0){
			if(xEnd == xStart +1 && yEnd == yStart +2){
				return 1;	
			}
		}
	}	
	//+1 -2
	if(xStart +1 <8 && xStart +1 >=0){
		if(yStart -2 <8 && yStart -2 >=0){
			if(xEnd == xStart +1 && yEnd == yStart -2){
				return 1;
			}	
		}
	}	
	//-2 +1
	if(xStart -2 <8 && xStart -2 >=0){
		if(yStart +1 <8 && yStart +1 >=0){
			if(xEnd == xStart -2 && yEnd == yStart +1){
				return 1;	
			}
		}
	}	
	//-2 -1
	if(xStart -2 <8 && xStart -2 >=0){
		if(yStart -1 <8 && yStart -1 >=0){
			if(xEnd == xStart -2 && yEnd == yStart -1){
				return 1;	
			}
		}
	}	
	//-1 +2
	if(xStart -1 <8 && xStart +2 >=0){
		if(yStart +2 <8 && yStart +2 >=0){
			if(xEnd == xStart -1 && yEnd == yStart +2){
				return 1;	
			}
		}

	}	
	//-1 -2
	if(xStart -1 <8 && xStart -2 >=0){
		if(yStart -2 <8 && yStart -2 >=0){
			if(xEnd == xStart -1 && yEnd == yStart -2){
				return 1;	
			}
		}
	}	

return 0;

}//end KnightFlag
static int BishopFlag(int xStart,int yStart,int xEnd,int yEnd,PieceData TempBoard[8][8]){
	//Diagonally Right Up +i +i
	int i;
	if(yEnd > yStart && xEnd > xStart){
   		for(i = 1; i<8; i++){
   			if(xStart +i<8 && xStart +i >= 0){//Check that it is withinbounds
				if(yStart +i<8 && yStart +i >= 0){
					if( (xStart +i == xEnd) && (yStart +i == yEnd)){
						return 1;
					}
					else if(TempBoard[xStart +i][yStart+i].value !=0){
						return 0;
					}//innest if	
				}	
			}
		}//end for
	}
	//Diagonally Left Up -i +i
	if(yEnd > yStart && xEnd < xStart){
   		for(i = 1; i<8; i++){
   			if(xStart -i<8 && xStart -i >= 0){
				if(yStart +i<8 && yStart +i>=0){
					if((xStart -i == xEnd) && (yStart +i == yEnd)){
						return 1;
					}
					else if(TempBoard[xStart -i][yStart+i].value !=0){
						return 0;
					}//innest if	
				}	
			}
		}//end for
	}//end if

	//Diagonally Right Down +i -i
	if(xEnd > xStart && yEnd < yStart){
   		for(i = 1; i<8; i++){
   			if(xStart +i<8 && xStart +i >= 0){
				if(yStart -i<8 && yStart -i>= 0){
					if( (xStart +i == xEnd) && (yStart - i == yEnd)){
						return 1;
					}
					else if(TempBoard[xStart +i][yStart-i].value !=0){
						return 0;
					}//innest if	
				}	
			}
		}//end for
	}//end if

	//Diagonally Right Up -i -i
	if(xEnd < xStart && yEnd < yStart){
   		for(i = 1; i<8; i++){
   			if(xStart -i<8 && xStart -i >= 0){
				if(yStart -i<8 && yStart -i>=0){
					if((xStart - i == xEnd) && (yStart -i == yEnd)){
						return 1;
					}
					else if(TempBoard[xStart -i][yStart-i].value !=0){
						return 0;
					}//innest if	
				}	
			}
		}//end for
		return 0;
	}//end if
	return 0;
}//end BishopFlag function
static int RookFlag(int xStart,int yStart,int xEnd,int yEnd,PieceData TempBoard[8][8]){
	int i=0;
	int move = -1;
	if(xStart < xEnd && yStart == yEnd){	//moving right
		move = 1;
	}else if(xStart > xEnd && yStart == yEnd){	//moving left
		move = 2;
	}else if(xStart == xEnd && yStart > yEnd){	//moving down
		move = 3;
	}else if(xStart == xEnd && yStart < yEnd){	//moving up
		move = 4;
	}else{
		return 0;		//break if not moving up down left or right
	}

	if(move ==1){ //check for moves in between right
   		for(i = 1; xStart + i <8; i++){
			if(xStart + i == xEnd && yStart == yEnd){
				return 1;
			}
			if(TempBoard[xStart +i][yStart].value !=0){
				return 0;
			}
		}
	}		
	if(move == 2){ //check for moves in between left
   		for(i = 1; xStart - i >= 0; i++){
			if(xStart - i == xEnd && yStart == yEnd){
				return 1;
			}
			if(TempBoard[xStart - i][yStart].value !=0){
				return 0;
			}
		}
	}
	if(move == 3){ //check for moves in between down	
   		for(i = 1; yStart - i >=0 ; i++){
			if(xStart == xEnd && yStart - i == yEnd){
				return 1;
			}
			if(TempBoard[xStart][yStart - i].value !=0){
				return 0;
			}
		}
	}
	if(move == 4){ //check for moves in between up	
   		for(i = 1; yStart + i<8; i++){
			if(xStart == xEnd && yStart+ i == yEnd){
				return 1;
			}
			if(TempBoard[xStart][yStart+i].value !=0){
				return 0;
			}
		}
	}
printf("Rook Error...Aborting...");
	exit(10);
	return -1;

}

static int QueenFlag(int xStart, int yStart, int xEnd, int yEnd,PieceData TempBoard[8][8]){
	if(RookFlag(xStart,yStart,xEnd,yEnd,TempBoard) == 1 || BishopFlag(xStart,yStart,xEnd,yEnd,TempBoard) == 1){
		return 1;		// no reason to rewrite, if legal for rook or bishop then legal for queen
	}else{
		return 0;
	}
}
static int KingFlag(int xStart, int yStart, int xEnd, int yEnd){
	if(xStart + 1 == xEnd && yStart == yEnd){	//to the right
		return 1;
	}else if(xStart - 1 == xEnd && yStart == yEnd){ //to the left
		return 1;
	}else if(xStart == xEnd && yStart + 1 == yEnd){ //above
		return 1;
	}else if(xStart == xEnd && yStart - 1 == yEnd){ //below
		return 1;
	}else if(xStart + 1 == xEnd && yStart + 1 == yEnd){ //top right
		return 1;
	}else if(xStart - 1 == xEnd && yStart + 1 == yEnd){ //top left
		return 1;
	}else if(xStart + 1 == xEnd && yStart - 1 == yEnd){ //bottom right
		return 1;
	}else if(xStart - 1 == xEnd && yStart - 1 == yEnd){ //bottom left
		return 1;
	}else{
			return 0;
	}
}
