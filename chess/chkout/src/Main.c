/* Program authors: Yousef Althaqeb, Nicolas Chen, Hugh Fong
 *			Brandon H Lam, Quyen B To
 *
 * Created: January 21, 2018
 * 
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AI.h"
#include "Constants.h"
#include "Movement.h"
#include "FileIO.h"
#include "LegalMoveChecker.h"
#include "FileIO.h"
#include "Conditionals.h"
#include <unistd.h>
void BoardValues(){
	int x,y;
	for(x=0;x<4;x++){
		for(y=0;y<4;y++){
			Board[x][y].BoardValue=.05*(x+1)*(y+1);
		}
	}
        for(x=0;x<4;x++){
                for(y=0;y<4;y++){
                        Board[7-x][7-y].BoardValue=.05*(x+1)*(y+1);
                }
        }

}

PieceData InitializeNewBoard(int posx, int posy )
{
	PieceData temporary;
	if( posy == 1)
	{
		temporary.value = 1;          /*SET WHITE PAWNS*/
		temporary.color = 'w';
		return temporary;
	}

	else if( posy == 6)
	{
		temporary.value = 1;
		temporary.color =  'b';         /*SET BLACK PAWNS*/
		return temporary;
	}

	else if( (posx == 0 && posy == 0) || (posx == 7 && posy == 0) )
	{
		temporary.value = 5;
		temporary.color	= 'w';		/*SET WHITE ROOK*/
		return temporary;
	}

	else if( (posx == 1 && posy == 0) || (posx == 6 && posy == 0) )
	{
		temporary.value = 3;
		temporary.color = 'w';		/*SET WHITE KNIGHTS*/
		return temporary;
	}

	else if( (posx == 2 && posy == 0) || (posx == 5 && posy == 0) )
	{
		temporary.value = 4;
		temporary.color = 'w';          /*SET WHITE BISHOP*/
		return temporary;
	}

	else if( posx == 3 && posy == 0)
	{
		temporary.value = 9;
		temporary.color = 'w';	     /*SET WHITE QUEEN*/
		return temporary;
	}

	else if( posx == 4 && posy == 0)
	{
		temporary.value = 50;		/*SET WHITE KING*/
		temporary.color = 'w';
		return temporary;
	}

	else if( (posx == 0 && posy == 7) || (posx == 7 && posy == 7) )
	{
		temporary.value = 5;
		temporary.color	= 'b';          /*SET BLACK ROOK*/
		return temporary;
	}

	else if( (posx == 1 && posy == 7) || (posx == 6 && posy == 7) )
	{
		temporary.value = 3;
		temporary.color = 'b'; 		/*SET BLACK KNIGHTS*/
		return temporary;
	}

	else if( (posx == 2 && posy == 7) || (posx == 5 && posy == 7) )
	{
		temporary.value = 4;
		temporary.color = 'b';		/*SET BLACK BISHOP*/
		return temporary;
	}

	else if( posx == 3 && posy == 7)
	{
		temporary.value = 9;
		temporary.color = 'b';         /*SET BLACK QUEEN */
		return temporary;
	}

	else if( posx == 4 && posy == 7)
	{
		temporary.value = 50;
		temporary.color = 'b';           /*SET BLACK KING */
		return temporary;
	}

	else
	{
		temporary.value = 0;
		temporary.color = ' ';
		return temporary;
	}
}

void PrintDead()
{
	int WR = 0, WN = 0, WB = 0, WQ = 0, WK = 0, WP = 0; 
	int BR = 0, BN = 0, BB = 0, BQ = 0, BK = 0, BP = 0;
	int i, j;
	for(i = 0; i <= 7; i++)
	{
	    for(j= 0; j <= 7; j++)
	    {
		if( Board[i][j].value == 1 && Board[i][j].color == 'w')              WP = WP + 1;
		else if( Board[i][j].value == 5 && Board[i][j].color == 'w')         WR = WR + 1;
		else if( Board[i][j].value == 3 && Board[i][j].color == 'w')	    WN = WN + 1;
		else if( Board[i][j].value == 4 && Board[i][j].color == 'w')	    WB = WB + 1;
		else if( Board[i][j].value == 9 && Board[i][j].color == 'w')	    WQ = WQ + 1;
		else if( Board[i][j].value == 50 && Board[i][j].color == 'w')  	    WK = WK + 1;
													/*Count pieces on board*/
		else if( Board[i][j].value == 1 && Board[i][j].color == 'b')	    BP = BP + 1;
		else if( Board[i][j].value == 5 && Board[i][j].color == 'b')	    BR = BR + 1;
		else if( Board[i][j].value == 3 && Board[i][j].color == 'b')	    BN = BN + 1;
		else if( Board[i][j].value == 4 && Board[i][j].color == 'b')	    BB = BB + 1;
		else if( Board[i][j].value == 9 && Board[i][j].color == 'b')	    BQ = BQ + 1;
		else if( Board[i][j].value == 50 && Board[i][j].color == 'b')	    BK = BK + 1;

	    }
	}

	printf("Dead Pieces: ");
	if( WP < 8 && BQ > 1) 
		for(i = BP + (BQ - 1); i < 8; i++)     printf("bP ");
	else if( WP < 8 && BR > 2)
		for(i = WP + (WR - 2); i < 8; i++)     printf("bP ");
	else if( WP < 8 && WB > 2)
		for(i = BP + (BB - 2); i < 8; i++)     printf("bP ");
	else if( WP < 8 && WN > 2)
		for(i = WP + (WN - 2); i < 8; i++)     printf("bP ");
	else
		for(i = WP; i < 8; i++) 	       printf("wP ");
	if (WR < 2)
		for(i = WR; i < 2; i++) 	       printf("wR ");
	if (WN < 2)
		for(i = WN; i < 2; i++) 	       printf("wN ");
	if (WB < 2) 
		for(i = WB; i < 2; i++) 	       printf("wB ");
	if (WQ < 1) 				       printf("wQ ");

	printf("\n             ");						/*Prints missing pieces*/
	if( BP < 8 && BQ > 1) 
		for(i = BP + (BQ - 1); i < 8; i++)     printf("bP ");
	else if( BP < 8 && BR > 2)
		for(i = BP + (BR - 2); i < 8; i++)     printf("bP ");
	else if( BP < 8 && BB > 2)
		for(i = BP + (BB - 2); i < 8; i++)     printf("bP ");
	else if( WP < 8 && BN > 2)
		for(i = BP + (BN - 2); i < 8; i++)     printf("bP ");
	else 
		for(i = BP; i < 8; i++) 	       printf("bP ");
	if (BR < 2)
		for(i = BR; i < 2; i++) 	       printf("bR ");
	if (BN < 2)
		for(i = BN; i < 2; i++) 	       printf("bN ");
	if (BB < 2) 
		for(i = BB; i < 2; i++) 	       printf("bB ");
	if (BQ < 1) 				       printf("bQ ");
	printf("\n..............................................\n");
}      


int KingCastle( char color )
{
	int checkkingwhite = 0, checkkingblack = 0;
	checkkingwhite = checkkingwhite + CheckKing(Board, 'w', 5, 0);
	checkkingwhite = checkkingwhite + CheckKing(Board, 'w', 6, 0);
	checkkingblack = checkkingblack + CheckKing(Board, 'b', 5, 7);
	checkkingblack = checkkingblack + CheckKing(Board, 'b', 6, 7);

	if( Board[4][0].value == 50 && Board[4][0].color == color && checkkingwhite == 0)
	{
		if(Board[5][0].value == 0 && Board[6][0].value == 0 && Board[7][0].value == 5 && Board[7][0].color == color )
			return 1;
		else return 0;
	}

	else if( Board[4][7].value == 50 && Board[4][7].color == color && checkkingblack == 0)
	{
		if(Board[5][7].value == 0 && Board[6][7].value == 0 && Board[7][7].value == 5 && Board[7][7].color == color )
			return 1;
		else return 0;
	}
		return 0;

}

int QueenCastle( char color )
{
	int checkkingwhite = 0, checkkingblack = 0;
	checkkingwhite = checkkingwhite + CheckKing(Board, 'w', 1, 0);
	checkkingwhite = checkkingwhite + CheckKing(Board, 'w', 2, 0);
	checkkingwhite = checkkingwhite + CheckKing(Board, 'w', 3, 0);
	checkkingblack = checkkingblack + CheckKing(Board, 'b', 1, 7);
	checkkingblack = checkkingblack + CheckKing(Board, 'b', 2, 7);
	checkkingblack = checkkingblack + CheckKing(Board, 'b', 3, 7);

	if( Board[4][0].value == 50 && Board[4][0].color == color && checkkingwhite == 0)
	{
		if(Board[3][0].value == 0 && Board[2][0].value == 0 && Board[1][0].value == 0 && Board[0][0].value == 5 && Board[0][0].color == color ) 
			return 1;
		else return 0;
	}

	if( Board[4][7].value == 50 && Board[4][7].color == color && checkkingblack == 0)
	{
		if(Board[3][7].value == 0 && Board[2][7].value == 0 && Board[1][7].value == 0 && Board[0][7].value == 5 && Board[0][7].color == color )
			return 1;
		else return 0;
	}
	return 0;
}

int main()
{
	time_t timebegin = time(NULL);
	time_t timeend = time(NULL);
	int totaltime1=0; int totaltime2=0; int timediff=0; //initialized to 0 so we dont get errors
	int totaltimesec=0; int totaltimemin=0; int totaltimehr=0;
	int i, j, AIorHuman = 0;  
	int continu = 1, game = 1, loop = 1, loop2 = 1;
	int side = 0;
	int mode=2, move, legal, level = 1;
	int blackqueencast = 0, whitequeencast = 0;
	int blackkingcast = 0, whitekingcast = 0;
	char AIcolor1 = 'w';
	char AIcolor2 = 'b';
	char new_or_load[10];
	char mode_char[5];
	char contin[5];
	char color[10];
	char difficulty[5];
	char moveto[15];
	char movefrom[15];
	int CastK, CastQ;
	int Check;
	WriteLog("  ","  ", 1);
	DeleteLog();
	WriteLog("  ","  ", 1);
	BoardValues();
	while(continu == 1)
	{
	   loop = 1;
	   Check = 0;
	   while(game == 1)
	   {
		while(loop == 1)
		{
		   printf("Load game or New Game (New|Load): ");
		   scanf("%s", new_or_load);
		   if(new_or_load[0] == 'N' || new_or_load[0] == 'n') /*Only need 1st letter*/
		   {
			blackqueencast = 0;
			blackkingcast = 0;
			whitekingcast = 0;
			whitequeencast = 0;
			totaltime1 = 0;
			totaltime2 = 0; 
			for(i = 0; i <= 7; i++)
			    for(j = 0; j <= 7; j++)
				Board[i][j] = InitializeNewBoard( i, j);

			while(loop2 == 1)
			{
			    printf("Playing Mode - (pvp|pvc|cvc) : ");
			    scanf("%s", mode_char);
			    if (mode_char[0] == 'p' && mode_char[2] == 'p')
			    {
				mode = 1;					/*If pvp*/
				loop2 = 0;
				AIorHuman = 1;
			    }
			    else if (mode_char[0] == 'p' && mode_char[2] == 'c')
			    {
				mode = 2;					/*If pvc*/
				loop2 = 0;
				AIorHuman = 1;
			    }
			    else if (mode_char[0] == 'c' && mode_char[2] == 'c')
			    {
				mode = 3;					/*If cvc*/
				loop2 = 0;
			    }
			    else
				printf("Oops. Option not available! \n");
			}

			loop2 = 1;
			while(mode > 1 && loop2 == 1)
			{
			   printf("AI Level - (easy|medium|hard) : ");
			   scanf("%s", difficulty);
			   if( difficulty[0] == 'e' || difficulty[0] == 'E')
			   {
				printf("Easy Mode has been selected. \n");    /*EASY MODE*/
				level = 1;
				loop2 = 0;
			   }
			   else if( difficulty[0] == 'm' || difficulty[0] == 'M')
			   {
				printf("Medium Mode has been selected. \n");    /*MEDIUM MODE*/
				level = 2;
				loop2 = 0;
			   }
			   else if( difficulty[0] == 'h' || difficulty[0] == 'H')
			   {
				printf("Hard Mode has been selected. \n");		
				level = 3;
				loop2 = 0;
			   }
			   else
				printf("OOps. Option not available! \n");

			}

			loop2 = 1;
			
			while(loop2 == 1 && mode == 2)   /*Side only matters when player vs bot*/
			{
			   printf("Color - (black|white) : ");
			   scanf("%s", color);
			   if( color[0] == 'w' || color[0] == 'W')
			   {
				AIcolor1 = 'b';
				side = 0;                  /*If you choose white, AI is black*/
				loop2 = 0;
			   }
			   else if(color[0] == 'b' || color[0] == 'B')
			   {
				AIcolor1 = 'w';
				side = 1;                  /*If you choose black, AI is white*/
				loop2 = 0;
			   }

			}

			loop = 0;

		   }/*if new_or_load bracket */

		   else if(new_or_load[0] == 'l' || new_or_load[0] == 'L')
		   {    
			if (access("./bin/data.txt", F_OK) != -1){                        
			char *a = LoadGame();
			mode = (int)a[4]-48;
			/*printf("%d",(int)a[4]);*/
			level = (int)a[5]-48;
			/*mode = 1;*/
			/*level = 0;*/
			AIcolor1 = 'b';
			side = 0;
			free(a);
			}
			else{
			printf("error no save file");
			continue;
}
			loop = 0;
		   }

		}   /*while loop1 bracket*/

		if( (mode < 3 && side == 0) || mode == 1)
		{    printboard(0);
		     PrintDead();
		     printf("Moves must follow format of MoveFrom MoveTo in capital letters.\n");
		     printf("Additional Options: Quit Game, Save Game, Undo Move, Hint Please.\n");
		     printf("Examples:  A2 A3;  KingSide Castle;  QueenSide Castle.\n\n");
		     CastK = 0;
		     CastQ = 0;
		     AIorHuman = 1;
		     legal = 0;
		     while(legal != 1)
		     {
			   timebegin = time(0); 
			   printf("White Move: ");
			   scanf("%s", movefrom);
			   scanf("%s", moveto);
			   timeend = time(0);
			   if ( (movefrom[0] == 'u' || movefrom[0] == 'U') && movefrom[3] == 'o')
               		   {
                   		Undo(mode);
				printboard(0);
				printf("White Move: ");
				scanf("%s", movefrom);
			        scanf("%s", moveto);
                   		break;
               		   }
			   
			   if( movefrom[0] == 'S' || movefrom[0] == 's')
			   {
				SaveGame(mode, level);
				printf("The game has been saved. \n");
				continue;
			   }

			   if( movefrom[2] == 'i' && movefrom[3] == 't')
			   	break;            /*Quit*/

			   if( movefrom[2] == 'n' && movefrom[3] == 't')
			   {
				AIMove('w', 3, 1);    /*Hint*/
				continue;
			   }

			   if(moveto[1] == 'a' && moveto[2] == 's')   
			   {
				if(movefrom[1] == 'i')              /*Ignore first letter bc dont care if capital*/
					CastK = KingCastle( 'w' );
				else if(movefrom[1] == 'u')
					CastQ = QueenCastle( 'w' ); 
				else
				{
				     printf("Castling not available. \n\n");
				     continue;	
				}
				if (CastK == 1 && whitekingcast == 0)
				{	
				     whitekingcast = 1;
				     Board[4][0].value = 0;
				     Board[4][0].color = ' ';
				     Board[7][0].value = 0;
				     Board[7][0].color = ' ';         /*Kingside Castling*/
				     Board[6][0].value = 50;
				     Board[6][0].color = 'w';
				     Board[5][0].value = 5;
				     Board[5][0].color = 'w';
				     break;
				}
				else if( CastQ == 1 && whitequeencast == 0)
				{
				     whitequeencast = 1;
				     Board[4][0].value = 0;
				     Board[4][0].color = ' ';
				     Board[0][0].value = 0;
				     Board[0][0].color = ' ';         /*Queenside Castling*/
				     Board[1][0].value = 50;
				     Board[1][0].color = 'w';
				     Board[2][0].value = 5;
				     Board[2][0].color = 'w';
				     break;
				}

				else 
				{
				     printf("The Castling option is not available.\n");
				     continue;
				}

			   }
		   	   legal = LegalMoveChecker(Board, movefrom, moveto, 'w',0); 
			   if( legal == 1)
			   {
				    timediff = (int)difftime(timeend, timebegin);
				    totaltime1 = totaltime1 + timediff;   
				    totaltimesec = totaltime1 % 60;
				    totaltimemin = (totaltime1 /60) % 60;
				    totaltimehr = (totaltime1 /60) / 60;
				    if (movefrom[0] == 'A' && movefrom[1] == '1') whitequeencast = 1;
				    else if (movefrom[0] == 'E' && movefrom[1] == '1') whitekingcast = 1;
				    else if (movefrom[0] == 'H' && movefrom[1] == '1') 
				    {
					whitequeencast = 1;
					whitekingcast = 1;
				    } 
				    move = movementfunction( movefrom, moveto, AIorHuman);
				    WriteLog(movefrom, moveto, AIorHuman); 
				    printboard(0);
				    PrintDead();
				    printf("Time taken for turn: %d seconds.\n", timediff);
				    printf("Total time taken: %d hr %d min %d sec.\n\n", totaltimehr, totaltimemin, totaltimesec); 
				    Promotion(1);
			   }
			   else printf("Illegal Move. \n\n");
		     }
		}

		else if (~((movefrom[0] == 'u' || movefrom[0] == 'U') && movefrom[3] == 'o'))
		{
		      AIMove(AIcolor1, level, 0);
		      Promotion(0);
		      printboard(0);
		      PrintDead();
		}

		if(movefrom[2] == 'i' && movefrom[3] == 't')
			break;

		Check = Checkmate(Board, 'w');
		if (Check == 1) break;

		if( (mode < 3 && side == 1) || mode == 1)
		{
		     printboard(1);
		     PrintDead();
		     printf("Moves must follow format of MoveFrom MoveTo in capital letters.\n");
		     printf("Additional Options: Quit Game, Save Game, Undo Move, Hint Please.\n");
		     printf("Examples:  A2 A3;  KingSide Castle;  QueenSide Castle\n\n");	
		     CastK = 0;
		     CastQ = 0;
		     AIorHuman = 2;
		     legal = 0;
		     while(legal != 1)
		     {
			   timebegin = time(0);   
			   printf("Black Move: ");
			   scanf("%s", movefrom);
			   scanf("%s", moveto);
			   timeend = time(0);
			   if ( (movefrom[0] == 'u' || movefrom[0] == 'U') && movefrom[3] == 'o')
               		   {
                   		Undo(mode);
				printboard(1);
				printf("Black Move: ");
 				scanf("%s", movefrom);
				scanf("%s", moveto);
				break;
               		   }
			   if (movefrom[2] == 'i' && movefrom[3] == 't') 
				break;				/*   Quitting */

			   if (movefrom[0] == 'S' || movefrom[0] == 's')
			   {
				SaveGame();
				printf("The game has been saved.\n");
				continue;
			   }

			   if (movefrom[2] == 'n' || movefrom[3] == 't')
			   {
				AIMove( 'b', 3, 1);   /*Hint*/
				continue;
			   }

			   if (moveto[1] == 'a' && moveto[2] == 's')   
			   {
				if(movefrom[1] == 'i')              /*Ignore first letter bc dont care if capital*/
					CastK = KingCastle( 'b' );
				else if(movefrom[1] == 'u')
					CastQ = QueenCastle( 'b' );
				else
				{
				     printf("Castling not available. \n\n");
				     continue;	
				}
				if (CastK == 1 && blackkingcast == 0 )
				{	
				     blackkingcast = 1;
				     Board[4][7].value = 0;
				     Board[4][7].color = ' ';
				     Board[7][7].value = 0;
				     Board[7][7].color = ' ';         /*Kingside Castling*/
				     Board[6][7].value = 50;
				     Board[6][7].color = 'b';
				     Board[5][7].value = 5;
				     Board[5][7].color = 'b';
				     break;
				}
				else if( CastQ == 1 && blackqueencast == 0)
				{
				     blackqueencast = 1;
				     Board[4][7].value = 0;
				     Board[4][7].color = ' ';
				     Board[0][7].value = 0;
				     Board[0][7].color = ' ';         /*Queenside Castling*/
				     Board[1][7].value = 50;
				     Board[1][7].color = 'b';
				     Board[2][7].value = 5;
				     Board[2][7].color = 'b';
				     break;
				}
				else 
				{	
					printf("The Castling option is not available.\n");
					continue;
				}
			   }

			   legal = LegalMoveChecker(Board,movefrom, moveto, 'b',0); 
			   if (legal == 1)
			   {
				    timediff = (int)difftime(timeend, timebegin);
				    if (mode == 2)
				    {
					totaltime1 = totaltime1 + timediff;
					totaltimesec = totaltime1 % 60;
					totaltimemin = (totaltime1 /60) % 60;
					totaltimehr = (totaltime1 / 60) / 60;
				    }
				    else if (mode == 1)
				    {
					totaltime2 = totaltime2 + timediff; 
					totaltimesec = totaltime2 % 60;
					totaltimemin = (totaltime2 / 60) % 60;
					totaltimehr = (totaltime2 /60) / 60;
				    }
				    if( movefrom[0] == 'A' && movefrom[1] == '8') blackqueencast = 1;
				    else if (movefrom[0] == 'E' && movefrom[1] == '8') blackkingcast = 1;
				    else if (movefrom[0] == 'H' && movefrom[1] == '8') 
				    {
					blackqueencast = 1;
					blackkingcast = 1;
				    }  
				    move = movementfunction( movefrom, moveto, AIorHuman);
				    WriteLog( movefrom, moveto, AIorHuman);
				    printboard(0);
				    PrintDead();
				    printf("Time taken for turn: %d .\n", timediff);
				    printf("Total time taken: %d hr %d min %d sec. \n\n", totaltimehr, totaltimemin, totaltimesec);   
				    Promotion(1);
			   } 				
			   else printf("Illegal Move. \n\n");

		     }   /*While Not Legal Move*/
		
		}      /*If(mode >3....) bracket*/
	
		else if(~((movefrom[0] == 'u' || movefrom[0] == 'U') && movefrom[3] == 'o'))
		{
		     if (mode == 3)
			AIMove(AIcolor2, level, 0);
		     else
		     	AIMove(AIcolor1, level, 0);
		     printboard(0);
		     PrintDead();
		     Promotion(0);
		}	

		if(movefrom[2] == 'i' &&  movefrom[3] == 't')
			break;

		Check = Checkmate(Board, 'b');
		if (Check == 1)    break;

	   }	/*while game bracket*/

	   loop2 = 1;
	   while(loop2 == 1)
	   {
	        printf("Would you like to play again? (Yes | No) :  ");
	        scanf("%s", contin);
	        if( contin[0] == 'N' || contin[0] == 'n')
		{
			continu = 0;
			loop2 = 0;
		}
		else if( contin[0] == 'Y' || contin[0] == 'y')
		{
			loop2 = 0;
		}
		else printf("Oops. Option not available.");
	   }

	} /* while continu bracket*/

	return 0;

}  /*End of main */
