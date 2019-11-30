#include "Conditionals.h"
#include "Constants.h"
#include "Conversion.h"
#include "LegalMoveChecker.h"
#include <stdio.h>
/*
static int GetKingX();
static int GetKingY();
*/
//int CheckUnderAttack(char playerColor);

#include <stdlib.h>
//static int GetKingX(PieceData tempBoard[8][8]);
//static int GetKingY(PieceData tempBoard[8][8]);
//static int WhoCheckKing();
//static int IsPinned(int xPos, int yPos);
//static PieceData *CheckUnderAttack(int pos1, int pos2);

//Promotion:
void Promotion(int AI){
	PieceData promoPiece;
	promoPiece.value = 0;
	promoPiece.color = ' ';
	char userChoice;
	// gets the color of the piece moved
	for(int i=0; i<8;i++){//Check 1st and 8th row
		
		int j = 0;	
		if(Board[i][j].value == 1  || Board[i][j].value ==1){//Check if piece is a pawn
			if(AI == 0){
				promoPiece.value = 9;
				promoPiece.color = Board[i][j].color;
				Board[i][j].value = promoPiece.value;
				Board[i][j].color = promoPiece.color;
				break;
			}
			printf("What piece would you like your pawn to be promoted to?\nEnter q for Queen\nb for bishop\nn for knight\n r for rook\n");//Asks user what they want to promote their pawn into
			scanf(" %c", &userChoice);//Takes in a user input
				
			if(userChoice == 'q'){
				promoPiece.value = 9; // set val of promoting piece to be a queen
				promoPiece.color = Board[i][j].color; //set the promotion piece's color
			}
			else if(userChoice == 'r'){
				promoPiece.value = 5; // set val of promoting piece to be a rook
				promoPiece.color = Board[i][j].color; //set the promotion piece's color
			}
			else if(userChoice == 'b'){
				promoPiece.value = 4; // set val of promoting piece to be a bishop
				promoPiece.color = Board[i][j].color; //set the promotion piece's color
				
			}
			else if(userChoice == 'n'){
				promoPiece.value = 3; // set val of promoting piece to be a knight
				promoPiece.color = Board[i][j].color; //set the promotion piece's color
			}
			Board[i][j].value = promoPiece.value;
			Board[i][j].color = promoPiece.color;
		}//end inner if
		j = 7;
		if(Board[i][j].value == 1  || Board[i][j].value ==1){//Check if piece is a pawn
			if(AI == 0){
				promoPiece.value = 9;
				promoPiece.color = Board[i][j].color;
				Board[i][j].value = promoPiece.value;
				Board[i][j].color = promoPiece.color;
				break;
			}

			printf("What piece would you like your pawn to be promoted to?\nEnter q for Queen\nb for bishop\nn for knight\n r for rook\n");//Asks user what they want to promote their pawn into
			scanf(" %c", &userChoice);//Takes in a user input
			if(userChoice == 'q'){
				promoPiece.value = 9; // set val of promoting piece to be a queen
				promoPiece.color = Board[i][j].color; //set the promotion piece's color
			}
			else if(userChoice == 'r'){
				promoPiece.value = 5; // set val of promoting piece to be a rook
				promoPiece.color = Board[i][j].color; //set the promotion piece's color
			}
			else if(userChoice == 'b'){
				promoPiece.value = 4; // set val of promoting piece to be a bishop
				promoPiece.color = Board[i][j].color; //set the promotion piece's color
				
			}
			else if(userChoice == 'n'){
				promoPiece.value = 3; // set val of promoting piece to be a knight
				promoPiece.color = Board[i][j].color; //set the promotion piece's color
			}
			Board[i][j].value = promoPiece.value;
			Board[i][j].color = promoPiece.color;
		}//end if
	}//end for
}//end Promotion function


//Was known as "CheckUnderAttack"
int CheckKing(PieceData tempBoard[8][8], char playerColor, int anotherX, int anotherY){
	int xCoordPiece = 0;
	int yCoordPiece = 0;
	//Check if it is going to be the King or another piece	
	if(anotherX == -1 && anotherY == -1){
		for(int i = 1; i<8; i++){
			for(int j=0; j<8; j++){
				if(tempBoard[i][j].value == 50){
					if(tempBoard[i][j].color == playerColor){
						xCoordPiece = i; //copying the row# the king is on
						yCoordPiece = j; //copying the col# the king is on
					}
				}//end if
			}//end inner for
		}//end for
	}
	else{
		xCoordPiece = anotherX;
		yCoordPiece = anotherY;
	}//end else
		
		//Start checking for Knight checks	
		//6ways for a knight to attack
		if( (xCoordPiece - 1 <= 7) && (xCoordPiece -1 >= 0)){
			if( (yCoordPiece -2 <= 7) && (yCoordPiece -2 >= 0) ){
				if( tempBoard[xCoordPiece -1][yCoordPiece -2].value == 3){//check if knight is at the potential knight attacking spot
					if( tempBoard[xCoordPiece -1][yCoordPiece -2].color != playerColor){//check if knight is at the potential knight attacking spot
						return 1;
					}
				}//3rd if
			}//2nd if
		}//outter if 
	
		if( (xCoordPiece -2 <= 7) && (xCoordPiece -2 >= 0)){
			if( (yCoordPiece -1 <= 7) && (yCoordPiece -1 >= 0) ){
				if(tempBoard[xCoordPiece -2][yCoordPiece -1].value == 3){//check if knight is at the potential knight attacking spot
					if(tempBoard[xCoordPiece -2][yCoordPiece -1].color != playerColor){//check if knight is at the potential knight attacking spot
						//printf("Knight ");
						return 1;
					}
				}//3rd if
			}//2nd if
		}//outter if 
		if( (xCoordPiece -2 <= 7) && (xCoordPiece -2 >= 0)   ){
			if( (yCoordPiece +1 <= 7) && (yCoordPiece +1 >= 0) ){
				if(tempBoard[xCoordPiece -2][ yCoordPiece +1].value == 3){//check if knight is at the potential knight attacking spot
					if(tempBoard[xCoordPiece -2][ yCoordPiece +1].color != playerColor){//check if knight is at the potential knight attacking spot
					//	printf("Knight ");
						return 1;
					}
				}//3rd if
			}//2nd if
		}//outter if 
		if( (xCoordPiece - 1 <= 7) && (xCoordPiece -1 >= 0)   ){
			if( (yCoordPiece +2 <= 7) && (yCoordPiece +2 >= 0) ){
				if(tempBoard[xCoordPiece -1][yCoordPiece +2].value == 3){//check if knight is at the potential knight attacking spot
					if(tempBoard[xCoordPiece -1][yCoordPiece +2].color != playerColor){//check if knight is at the potential knight attacking spot
					//	printf("Knight ");
						return 1;
					}
				}//3rd if
			}//2nd if
		}//outter if 
		if( (xCoordPiece +1 <= 7) && (xCoordPiece +1 >= 0)   ){
			if( (yCoordPiece +2 <= 7) && (yCoordPiece +2 >= 0) ){
				if(tempBoard[xCoordPiece +1][yCoordPiece +2].value == 3){//check if knight is at the potential knight attacking spot
					if(tempBoard[xCoordPiece +1][yCoordPiece +2].color != playerColor){//check if knight is at the potential knight attacking spot
					//	printf("Knight ");
						return 1;
					}
				}//3rd if
			}//2nd if
		}//outter if 
		if( (xCoordPiece +2 <= 7) && (xCoordPiece +2 >= 0)   ){
			if( (yCoordPiece +1 <= 7) && (yCoordPiece +1 >= 0) ){
				if(tempBoard[xCoordPiece +2][yCoordPiece +1].value == 3){//check if knight is at the potential knight attacking spot
					if(tempBoard[xCoordPiece +2][yCoordPiece +1].color != playerColor){//check if knight is at the potential knight attacking spot
					//	printf("Knight ");
						return 1;
					}
				}//3rd if
			}//2nd if
		}//outter if 
		
		if( (xCoordPiece +2 <= 7) && (xCoordPiece +2 >= 0)   ){
			if( (yCoordPiece -1 <= 7) && (yCoordPiece -1 >= 0) ){
				if(tempBoard[xCoordPiece +2][yCoordPiece -1].value == 3){//check if knight is at the potential knight attacking spot
					if(tempBoard[xCoordPiece +2][yCoordPiece -1].color != playerColor){//check if knight is at the potential knight attacking spot
					//	printf("Knight ");
						return 1;
					}
				}//3rd if
			}//2nd if
		}//outter if 
		if( (xCoordPiece +1 <= 7) && (xCoordPiece +1 >= 0)   ){
			if( (yCoordPiece -2 <= 7) && (yCoordPiece -2 >= 0) ){
				if(tempBoard[xCoordPiece +1][yCoordPiece -2].value == 3){//check if knight is at the potential knight attacking spot
					if(tempBoard[xCoordPiece +1][yCoordPiece -2].color != playerColor){//check if knight is at the potential knight attacking spot
					//	printf("Knight ");
						return 1;
					}
				}//end 3rd if
			}//end 2nd if
		}//end outter if 
	//done checking for Knight checks

	//checkBishop
	//4 ways a bishop can check the king (top left, top right, bottom left, bottom right)
	
	//checks bishop from diagonal top left
	for(int i =1; i<8; i++){
			if( (xCoordPiece -i <=7) && (xCoordPiece -i >=0) ){//column check within bounds
				if( (yCoordPiece +i <= 7) && (yCoordPiece +i >= 0) ){//row check within bounds
					if((tempBoard[xCoordPiece -i][yCoordPiece +i].value != 0 && tempBoard[xCoordPiece -i][yCoordPiece +i].color == playerColor)){
						break;
					}
					if((tempBoard[xCoordPiece -i][yCoordPiece +i].value !=9 &&tempBoard[xCoordPiece -i][yCoordPiece +i].value != 4 && tempBoard[xCoordPiece -i][yCoordPiece +i].color != playerColor && tempBoard[xCoordPiece -i][yCoordPiece +i].value != 0)){
						break;
					}
					if((tempBoard[xCoordPiece-i][yCoordPiece +i].value == 4)){
						if((tempBoard[xCoordPiece -i][yCoordPiece +i].color != playerColor)){
					//	printf("Bishop TL ");
							return 1;
						}
					}	
					else if ((tempBoard[xCoordPiece -i][yCoordPiece +i].value == 9)){
						if((tempBoard[xCoordPiece -i][yCoordPiece +i].color != playerColor)){
					//		printf("Bishop Queen TL ");
							return 1;
						}
					}
				}//end outter if	
			}//end inner for
	}
	
	//checks bishop from diagonal top right
	for(int i =1; i<8; i++){
			if( (xCoordPiece +i <=7) && (xCoordPiece +i >=0) ){//column check within bounds
				if((yCoordPiece +i <= 7) && (yCoordPiece +i >= 0) ){//row check within bounds
					if((tempBoard[xCoordPiece +i][yCoordPiece +i].value != 0 && tempBoard[xCoordPiece +i][yCoordPiece +i].color == playerColor)){
						break;
					}
					if((tempBoard[xCoordPiece +i][yCoordPiece +i].value != 9 &&tempBoard[xCoordPiece +i][yCoordPiece +i].value != 4 && tempBoard[xCoordPiece +i][yCoordPiece +i].color != playerColor && tempBoard[xCoordPiece +i][yCoordPiece +i].value != 0)){
						break;
					}
					if((tempBoard[xCoordPiece +i][yCoordPiece +i].value == 4)){
						if((tempBoard[xCoordPiece +i][yCoordPiece +i].color != playerColor)){
							//printf("Bishop TR ");
							return 1;
						}
					}
					else if((tempBoard[xCoordPiece +i][yCoordPiece +i].value == 9)){
						if((tempBoard[xCoordPiece +i][yCoordPiece +i].color != playerColor)){
					//		printf("Bishop Queen TR ");
							return 1;
						}
					}		
				}//end 2nd if	
			}//end outter if	
	}//end outter for
	
	//checks bishop from diagonal bottom right
	for(int i =1; i<8; i++){
			if( (xCoordPiece +i <=7) && (xCoordPiece +i >=0) ){//column check within bounds
				if( (yCoordPiece -i <= 7) && (yCoordPiece-i >= 0) ){//row check within bounds
					if((tempBoard[xCoordPiece +i][yCoordPiece -i].value != 0 && tempBoard[xCoordPiece +i][yCoordPiece -i].color == playerColor)){
						break;
					}
					if((tempBoard[xCoordPiece +i][yCoordPiece -i].value != 4 && tempBoard[xCoordPiece+i][yCoordPiece-i].value != 9 && tempBoard[xCoordPiece +i][yCoordPiece -i].color != playerColor && tempBoard[xCoordPiece +i][yCoordPiece -i].value != 0)){
						break;
					}
					if((tempBoard[xCoordPiece +i][yCoordPiece-i].value == 4)){
						if((tempBoard[xCoordPiece +i][yCoordPiece-i].color != playerColor)){
						//	printf("Bishop BR ");
							return 1;
						}
					}
					else if((tempBoard[xCoordPiece +i][yCoordPiece-i].value == 9)){
						
						if((tempBoard[xCoordPiece +i][yCoordPiece-i].color != playerColor)){
						//	printf("Bishop Queen BR ");
							return 1;
						}
					}		
				}//end 2nd if	
			}//end outter if	
	}//end outter for

	//checks bishop from diagonal bottom left
	for(int i =1; i<8; i++){
			if( (xCoordPiece -i <=7) && (xCoordPiece -i >=0) ){//column check within bounds
				if( (yCoordPiece -i <= 7) && (yCoordPiece-i >= 0) ){//row check within bounds
					if((tempBoard[xCoordPiece -i][yCoordPiece -i].value != 0 && tempBoard[xCoordPiece -i][yCoordPiece -i].color == playerColor)){
						break;
					}
					if((tempBoard[xCoordPiece-i][yCoordPiece+i].value != 9 && tempBoard[xCoordPiece -i][yCoordPiece -i].value != 4 && tempBoard[xCoordPiece -i][yCoordPiece -i].color != playerColor && tempBoard[xCoordPiece -i][yCoordPiece -i].value != 0 )){
						break;
					}
					if((tempBoard[xCoordPiece-i][yCoordPiece-i].value == 4)){
						if((tempBoard[xCoordPiece-i][yCoordPiece-i].color != playerColor)){
						//	printf("Bishop BL ");
							return 1;
						}
					}
					else if((tempBoard[xCoordPiece-i][yCoordPiece-i].value == 9)){
						
						if((tempBoard[xCoordPiece -i][yCoordPiece -i].value != 0 && tempBoard[xCoordPiece -i][yCoordPiece -i].color == playerColor)){
							break;
						}
						if((tempBoard[xCoordPiece-i][yCoordPiece-i].color != playerColor)){
						//	printf("Bishop Queen BL ");
							return 1;
						}
					}		
				}//end 2nd if	
			}//end outter if	
	}//end outter for	
	
	
	//checkRook
	//4 ways for rook to check king(up,down,left right)		
	//checks rook from top
	for(int i =1; i<8; i++){
		if( (xCoordPiece <=7) && (xCoordPiece >=0) ){//column check within bounds
			if( ((yCoordPiece+i) <= 7) &&( (yCoordPiece+i) >= 0) ){//row check within bounds
				if((tempBoard[xCoordPiece][yCoordPiece +i].value != 0 && tempBoard[xCoordPiece][yCoordPiece +i].color == playerColor)){
					break;
				}
				if((tempBoard[xCoordPiece][yCoordPiece+i].value != 9 && tempBoard[xCoordPiece][yCoordPiece +i].value != 5 && tempBoard[xCoordPiece][yCoordPiece +i].color != playerColor && tempBoard[xCoordPiece][yCoordPiece +i].value != 0   )){
					break;
				}
				if((tempBoard[xCoordPiece][yCoordPiece +i].value == 5)){
					if((tempBoard[xCoordPiece][yCoordPiece +i].color != playerColor)){
				//			printf("Rook T ");
						return 1;
					}
				}
				else if((tempBoard[xCoordPiece][yCoordPiece +i].value == 9)){
					if((tempBoard[xCoordPiece][yCoordPiece +i].color != playerColor)){
					//	printf("Rook Queen T ");
						return 1;
					}
				}		
			}//end 2nd if	
		}//end outter if	
	}//end for
	
	//checks rook from bottom
	for(int i =1; i<8; i++){
		if( (xCoordPiece <=7) && (xCoordPiece >=0) ){//column check within bounds
			if( ((yCoordPiece -i) <= 7) && ( (yCoordPiece-i) >= 0) ){//row check within bounds
				if((tempBoard[xCoordPiece][yCoordPiece-i].value != 0 && tempBoard[xCoordPiece][yCoordPiece -i].color == playerColor)){
					break;
				}
				if((tempBoard[xCoordPiece][yCoordPiece+i].value != 9 && tempBoard[xCoordPiece][yCoordPiece +i].value != 5 && tempBoard[xCoordPiece][yCoordPiece +i].color != playerColor) && tempBoard[xCoordPiece][yCoordPiece +i].value != 0    ){
					break;
				}
				
				if((tempBoard[xCoordPiece][yCoordPiece -i].value == 5)){
					if((tempBoard[xCoordPiece][yCoordPiece -i].color != playerColor)){
					//	printf("Rook B ");
						return 1;
					}
				}
				else if((tempBoard[xCoordPiece][yCoordPiece -i].value == 9)){
					
					if((tempBoard[xCoordPiece][yCoordPiece -i].color != playerColor)){
					//	printf("Rook Queen B ");
						return 1;
					}
				}		
			
			
			}//end 2nd if	
		}//end outter if	
	}//end for
	
	//checks rook from left
	for(int i =1; i<8; i++){

		if( (xCoordPiece -i <= 7) && (xCoordPiece -i >= 0) ){//row check within bounds
			if( (yCoordPiece<= 7) && (yCoordPiece>= 0) ){//row check within bounds
				
				if((tempBoard[xCoordPiece -i][yCoordPiece].value != 0 && tempBoard[xCoordPiece -i][yCoordPiece].color == playerColor)){
					break;
				}//checks that your own piece blocks it
				if((tempBoard[xCoordPiece-i][yCoordPiece].value != 9 && tempBoard[xCoordPiece -i][yCoordPiece].value != 5 && tempBoard[xCoordPiece -i][yCoordPiece].color != playerColor && tempBoard[xCoordPiece -i][yCoordPiece].value != 0 )){//new change added != 0
					break;
				}
				if((tempBoard[xCoordPiece -i][yCoordPiece].value == 5)){
					if((tempBoard[xCoordPiece -i][yCoordPiece].color != playerColor)){
					//	printf("Rook L ");
						return 1;
					}
				}
				else if((tempBoard[xCoordPiece -i][yCoordPiece].value == 9)){
					
					if((tempBoard[xCoordPiece -i][yCoordPiece].value != 0 && tempBoard[xCoordPiece -i][yCoordPiece].color == playerColor)){
						break;
					}
					if((tempBoard[xCoordPiece -i][yCoordPiece].color != playerColor)){
					//	printf("Rook Queen L");
						return 1;
					}
				}		
			}//end 2nd if	
		}//end outter if	
	}//end for

	//Checks Rook from right
	for(int i =1; i<8; i++){
		if( (xCoordPiece + i <= 7) && (xCoordPiece +i>= 0) ){//row check within bounds
			if( (yCoordPiece<= 7) && (yCoordPiece>= 0) ){//row check within bounds
				if((tempBoard[xCoordPiece +i][yCoordPiece].value != 0 && tempBoard[xCoordPiece +i][yCoordPiece].color == playerColor)){
					break;
				}
				if((tempBoard[xCoordPiece +i][yCoordPiece].value != 9 && tempBoard[xCoordPiece +i][yCoordPiece].value != 5 && tempBoard[xCoordPiece +i][yCoordPiece].color != playerColor  && tempBoard[xCoordPiece +i][yCoordPiece].value != 0)){
					break;
				}
				if((tempBoard[xCoordPiece +i][yCoordPiece].value == 5)){
					if((tempBoard[xCoordPiece +i][yCoordPiece].color != playerColor)){
					//	printf("Rook R ");
						return 1;
					}
				}
				else if((tempBoard[xCoordPiece +i][yCoordPiece].value == 9)){
					if((tempBoard[xCoordPiece +i][yCoordPiece].color != playerColor)){
					//	printf("Rook Q R");
						return 1;
					}
				}		
			}//end 3rd if
		}//end 2nd if	
	}//end for
	
	//Check Pawn
	//pawn attacks diagonally from King
	//must account for color
	if( tempBoard[xCoordPiece][yCoordPiece].color == 'w'){
		if(xCoordPiece -1 <=7 && xCoordPiece -1 >= 0){//check in range
			if(yCoordPiece +1 <=7 && yCoordPiece +1 >= 0){//check in range
				if( (tempBoard[xCoordPiece -1][yCoordPiece +1].color != 'w')){//check if a pawn is 1 square diagonal to the King
					if( (tempBoard[xCoordPiece -1][yCoordPiece +1].value == 1)){//check if a pawn is 1 square diagonal to the King
					//	printf("Pawn ");
						return 1;
					}	
				}
			}	
		}
	}

	if( tempBoard[xCoordPiece][yCoordPiece].color == 'w'){
		if(xCoordPiece -1 <=7 && xCoordPiece -1 >= 0){
			if(yCoordPiece +1 <=7 && yCoordPiece +1 >= 0){
				if( tempBoard[xCoordPiece +1][yCoordPiece +1].color != 'w'){
					if( (tempBoard[xCoordPiece +1][yCoordPiece+1].value == 1)){//check if a pawn is 1 square diagonal to the King
					//	printf("Pawn ");
						return 1;
					}
				}
			}	
		}
	}
		
	
	if( tempBoard[xCoordPiece][yCoordPiece].color == 'b'){
		if(xCoordPiece +1 <=7 && xCoordPiece +1 >= 0){
			if(yCoordPiece -1 <=7 && yCoordPiece -1 >= 0){
				if( (tempBoard[xCoordPiece+1][yCoordPiece-1].color != 'b')){//check if a pawn is 1 square diagonal to the King
					if( (tempBoard[xCoordPiece+1][yCoordPiece-1].value == 1)){//check if a pawn is 1 square diagonal to the King
					//	printf("Pawn ");
						return 1;
					}
				}
			}	
		}
	}

	if( tempBoard[xCoordPiece][yCoordPiece].color == 'b'){
		if(xCoordPiece -1 <=7 && xCoordPiece -1 >= 0){
			if(xCoordPiece -1 <=7 && xCoordPiece -1 >= 0){
				if( (tempBoard[xCoordPiece-1][yCoordPiece -1].color != 'b')){//check if a pawn is 1 square diagonal to the King
					if( (tempBoard[xCoordPiece-1][yCoordPiece -1].value == 1)){//check if a pawn is 1 square diagonal to the King
				//		printf("Pawn ");
						return 1;
					}
				}
			}	
		}
	}
	//King Check	
	for(int i = -1; i<2; i++){
		for(int j = -1; j<2; j++){
			if(xCoordPiece +i <= 7 && xCoordPiece +i >=0){ //within bounds of board
				if(yCoordPiece+ j <=7 && yCoordPiece + j>=0){ //within bounds of board
					if( tempBoard[xCoordPiece +i][yCoordPiece +j].value == 50){//check if king is at the potential knight attacking spot
						if( tempBoard[xCoordPiece +i][yCoordPiece +j].color != playerColor){//check if knight is at the potential knight attacking spot
						//	printf("King ");
							return 1;
						}
					}	
				}//3rd if
			}
		}
	}

	return 0;		
}//

//Checkmate Function
int Checkmate(PieceData tempBoard[8][8], char playerColor){
	char *MoveFrom = malloc(sizeof(char) *3);
	char *MoveTo = malloc(sizeof(char)*3);
	//go through all moves and see if I'm still in check
	for(int x=0; x<8; x++){
		for(int y =0; y<8; y++){
			if(tempBoard[x][y].value != 0 && tempBoard[x][y].color == playerColor){
				for(int i =0; i<8; i++){
					for(int j=0; j<8; j++){
						if(i ==x && j ==y){
							break;
						}			
						ConvertXY(x,y, MoveFrom);
						ConvertXY(i,j, MoveTo);
						if(tempBoard[i][j].color != playerColor){
							if(LegalMoveChecker(tempBoard,MoveFrom,MoveTo, playerColor,1) == 1){
								free(MoveFrom);
								free(MoveTo);
								return 0;
							}
						}
					}
				}//end inner fors
			}	
		}
	}
	free(MoveFrom);
	free(MoveTo);	
	printf("Checkmated");
	return 1;
}

