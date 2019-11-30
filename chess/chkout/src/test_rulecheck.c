#include "AI.h"
#include "Movement.h"
#include "Constants.h"
#include "Conditionals.h"
PieceData InitializeNewBoard(int posx, int posy );

int main(){
	int i, j;
	DeleteLog();
	WriteLog("  ","  ", 1);
	while(1){
		for(i = 0; i <= 7; i++){
		    for(j = 0; j <= 7; j++){
			Board[i][j] = InitializeNewBoard( i, j);
		    }
		}
		AIMove('w',3,0);
		printboard(0);
//		PrintDead();
		AIMove('b',3,0);
		printboard(0);
//		PrintDead();
	}
return 0;
}



PieceData InitializeNewBoard(int posx, int posy ){
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
