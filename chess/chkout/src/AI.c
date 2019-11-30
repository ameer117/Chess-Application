#include <string.h>
#include <time.h>
#include "AI.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef struct MD{
	int Move_1[5];
	int Move_2[5];
	int Move_3[5];
} MoveData;

/* Static Function Declarations */
static int EvaluateMove(PieceData *Temp,int x,int y);
static void EvaluateBestMove(PieceData *Temp,MoveData *Data, char color);
static int DetermineBestMove(PieceData *Temp,int *Data,char AIcolor, int UpperLimit);
static void StoreData(int *Data, int  x,int y,int i,int j,int MaxValue);
static long int FindBestDifference(int *Data,int Combinations);
static void ClearData(int *Data);
static void CopyBoard2(PieceData *New, PieceData *Old);
static MoveData *CreateNewData();
static PieceData *ConvertBoard();
static char FlipColor(char color);
static PieceData *Dynamic(int x,int y);
static MoveData *EvaluateMove1(MoveData *MoveData_1,char color,PieceData *Temp);
static MoveData *EvaluateMove2(MoveData *MoveData_1,char color,PieceData *Temp);
static MoveData *EvaluateMove3(MoveData *MoveData_1,char color,PieceData *Temp);
static int TakeDifferences(int *Data1, MoveData *Data2, MoveData *Data3,MoveData *Data4,MoveData *Data5);
static void ConvertBoard2D(PieceData N[8][8],PieceData *T);
static void ClearData2(int *Move);
static void PreventBug(int *move);

/* End of Static Function Declarations */
int Move1Parameter = 3;
int Move2Parameter = 3;
int Move3Parameter = 1;
char DefaultColor = 'w';
void AIMove(char color, int level,int hint){	
	srand(time(NULL));
	char *MoveFrom=malloc(sizeof(char)*3);
	char *MoveTo=malloc(sizeof(char)*3);
	int *KeepData;
	char AI_Color,Opposite_Color;

	if(color=='b'){
		AI_Color	='b';	//define colors based on inputted value from main.c
		Opposite_Color	='w';
		DefaultColor 	='b';
	}else{
		AI_Color	='w';
		Opposite_Color 	='b';
		DefaultColor	='w';
	}
	if(level==1){
		Move3Parameter=0;
		Move2Parameter=0;		//adjust parameters based on level
	}else if(level==2){
		Move3Parameter=0;
	}

	assert(AI_Color == 'w' || AI_Color == 'b');

	PieceData *NewBoard = ConvertBoard();

	/*	Begin Min-Maxing	*/
	
		/*Row 1*/
	MoveData *MoveData_1=CreateNewData();

	EvaluateBestMove(NewBoard,MoveData_1,AI_Color); //initial evaluate. Determines best 3 possible moves it can make and store them into data

		/*Row 2*/	
	PieceData *Temp0=Dynamic(8,8);	CopyBoard2(Temp0,NewBoard);			//creates new board
	PieceData *Temp1=Dynamic(8,8);	CopyBoard2(Temp1,NewBoard);			//creates new board for move 1.1
	PieceData *Temp2=Dynamic(8,8);	CopyBoard2(Temp2,NewBoard);			//creates new board
	
	MoveData *MoveData_2_1=EvaluateMove1(MoveData_1,AI_Color,Temp0);	//evaluate move 1.1 determine best moves enemy can make
	MoveData *MoveData_2_2=EvaluateMove2(MoveData_1,AI_Color,Temp1);
	MoveData *MoveData_2_3=EvaluateMove3(MoveData_1,AI_Color,Temp2);

		/*Row 3 */
	PieceData *Temp3=Dynamic(8,8);	CopyBoard2(Temp3,Temp0);			//creates new board
	PieceData *Temp4=Dynamic(8,8);	CopyBoard2(Temp4,Temp1);			//creates new board for 2.1
	PieceData *Temp5=Dynamic(8,8);	CopyBoard2(Temp5,Temp2);			//creates new board

	PieceData *Temp6=Dynamic(8,8);	CopyBoard2(Temp6,Temp0);			//creates new board
	PieceData *Temp7=Dynamic(8,8);	CopyBoard2(Temp7,Temp1);			//creates new board for 2.2
	PieceData *Temp8=Dynamic(8,8);	CopyBoard2(Temp8,Temp2);			//creates new board

	PieceData *Temp9=Dynamic(8,8);   CopyBoard2(Temp9,Temp0);			//creates new board
	PieceData *Temp10=Dynamic(8,8);	CopyBoard2(Temp10,Temp1);			//creates new board for 2.3
	PieceData *Temp11=Dynamic(8,8);	CopyBoard2(Temp11,Temp2);			//creates new board

	free(Temp0);
	free(Temp1);
	free(Temp2);

	MoveData *MoveData_3_1=EvaluateMove1(MoveData_2_1,Opposite_Color,Temp3);
	MoveData *MoveData_3_2=EvaluateMove2(MoveData_2_1,Opposite_Color,Temp4);	//evaluate move 2.1
	MoveData *MoveData_3_3=EvaluateMove3(MoveData_2_1,Opposite_Color,Temp5);

	MoveData *MoveData_3_4=EvaluateMove1(MoveData_2_2,Opposite_Color,Temp6);
	MoveData *MoveData_3_5=EvaluateMove2(MoveData_2_2,Opposite_Color,Temp7);	//evaluate move 2.2
	MoveData *MoveData_3_6=EvaluateMove3(MoveData_2_2,Opposite_Color,Temp8);

	MoveData *MoveData_3_7=EvaluateMove1(MoveData_2_3,Opposite_Color,Temp9);
	MoveData *MoveData_3_8=EvaluateMove2(MoveData_2_3,Opposite_Color,Temp10);	//evaluate move 2.3;
	MoveData *MoveData_3_9=EvaluateMove3(MoveData_2_3,Opposite_Color,Temp11);
	free(Temp3);free(Temp4);free(Temp5);free(Temp6);free(Temp7);free(Temp8);free(Temp9);free(Temp10);free(Temp11);
	
	/* INSERT MORE HERE IF WISH TO LOOK MORE MOVES AHEAD */

	int SaveMove1=TakeDifferences(MoveData_1->Move_1,MoveData_2_1,MoveData_3_1,MoveData_3_2,MoveData_3_3);
	int SaveMove2=TakeDifferences(MoveData_1->Move_2,MoveData_2_2,MoveData_3_4,MoveData_3_5,MoveData_3_6);
	int SaveMove3=TakeDifferences(MoveData_1->Move_3,MoveData_2_3,MoveData_3_7,MoveData_3_8,MoveData_3_9);
	int SaveMove;
	int *KeepMove=malloc(sizeof(int)*4);

	if(SaveMove1>=SaveMove2 && SaveMove1 >= SaveMove3){
		KeepData=MoveData_1->Move_1;
		SaveMove=SaveMove1;
	}else if(SaveMove2>=SaveMove1 && SaveMove2 >= SaveMove3){
		KeepData=MoveData_1->Move_2;
		SaveMove=SaveMove2;
	}else{
		KeepData=MoveData_1->Move_3;
		SaveMove=SaveMove3;
	}

	KeepMove[0]=KeepData[0];
	KeepMove[1]=KeepData[1];
	KeepMove[2]=KeepData[2];
	KeepMove[3]=KeepData[3];

	PreventBug(KeepMove);

	ConvertXY(KeepData[0],KeepData[1],MoveFrom);			//Convert into passable coordinates
	ConvertXY(KeepData[2],KeepData[3],MoveTo);
	if(hint==1){
		printf("Recommended Move: %s %s \n",MoveFrom,MoveTo);
	}else{
		LegalMovement(KeepMove,Board);
		WriteLog(MoveFrom,MoveTo,0);	
#ifdef DEBUG	
        	printf("Value of Move: %d \n",SaveMove);
#endif
        	printf("AI Move From:  %s \n",MoveFrom);	//print to terminal
        	printf("AI Move T0  :  %s \n",MoveTo);
	}
	free(MoveFrom);free(MoveTo);free(MoveData_1);free(MoveData_2_1);free(MoveData_2_2);free(MoveData_2_3);
	free(MoveData_3_1);free(MoveData_3_2);free(MoveData_3_3);free(MoveData_3_4);free(MoveData_3_5);
	free(MoveData_3_6);free(MoveData_3_7);free(MoveData_3_8);free(MoveData_3_9);
	free(KeepMove);free(NewBoard);
	MoveFrom=NULL;
	MoveTo=NULL;
}


static void EvaluateBestMove(PieceData *Temp,MoveData *Data,char AIcolor){
	int FirstBest,SecondBest,ThirdBest;
	FirstBest=DetermineBestMove(Temp, Data->Move_1, AIcolor, 1000);
	SecondBest=DetermineBestMove(Temp,Data->Move_2,AIcolor,FirstBest);
	ThirdBest=DetermineBestMove(Temp,Data->Move_3,AIcolor,SecondBest);
}

static int DetermineBestMove(PieceData *Temp,int *Data,char AIcolor,int UpperLimit){
	int CheckedValue=0;
	int MaxValue=0;
	int x,y,i,j;
	char *MoveFrom=malloc(sizeof(char)*3);
        char *MoveTo=malloc(sizeof(char)*3);
	if (!MoveFrom){perror("Out of memory! Aborting..."); exit(10);}
	if (!MoveTo){perror("Out of memory! Aborting..."); exit(10);}

	PieceData ConvertedTemp[8][8];
	ConvertBoard2D(ConvertedTemp,Temp);
	if(AIcolor==DefaultColor){
		ClearData(Data);
	}else{
		ClearData2(Data);
	}

        for(y=0;y<8;y++){			                                          //iterate through the board
                for(x=0;x<8;x++){                                                       //iterate through the board
                        if(Temp[x+8*y].value != 0 && Temp[x+8*y].color == AIcolor){       //if there is a piece on the board
                                for(j=0;j<8;j++){                                       // iterate through possible places to be moved on the board
                                        for(i=0;i<8;i++){                               //iterate through possible places to be moved onto the board
                                                if(i==x && j==y){                       // if move to position is the same as move from, ignore
                                                	break;
                                                }  
                                                ConvertXY(x,y,MoveFrom);                //convert format
                                                ConvertXY(i,j,MoveTo);                  //convert format
                                                if(Temp[i+8*j].color != AIcolor){         //if color of piece is correct, check for legality
                                                        CheckedValue = EvaluateMove(Temp,i,j); //value of move is returned
							if(UpperLimit > CheckedValue && CheckedValue >= MaxValue){ //if it is less than the highest value inputted    
	                                                      	 if(LegalMoveChecker(ConvertedTemp,MoveFrom,MoveTo,AIcolor,1)!=0){  //if move is legal, then copy value of move
									MaxValue=CheckedValue;		//assign new max value bc we determined new best move
									StoreData(Data,x,y,i,j,MaxValue); //copy new max move into move 1
								}
							}
                                                }
                                        }   
                                }   
                        }   
                }   
        } 
	free(MoveFrom);
	free(MoveTo);
	MoveFrom=NULL;
	MoveTo=NULL;
	return MaxValue;
}


static int EvaluateMove(PieceData *Temp,int x,int y){
	if (Temp[x+8*y].value ==50){
		return 12+Temp[x+8*y].BoardValue;
	}else{
        	return Temp[x+8*y].value+Temp[x+8*y].BoardValue;
	}
}
static void StoreData(int *Data,int x,int y,int i,int j,int MaxValue){
	Data[0]=(int)x;
	Data[1]=(int)y;
	Data[2]=(int)i;
	Data[3]=(int)j;
	Data[4]=(int)MaxValue;
	Data[5]='\0';
}
static long int FindBestDifference(int *Data,int Combinations){
 	int j=0;
	int BestValue=0;
 	for(j=0;j<Combinations;j++){
        	if(Data[j]>=BestValue){
		       BestValue=Data[j];                            //find out what the best trade would be
	        } 
	}
	return BestValue;
}

static void ClearData(int *Move){
	StoreData(Move,0,0,0,0,0);
}
/*static void ClearData2(int *Move){
	StoreData(Move,100,100,100,100,100);
}*/
static void ClearData2(int *Move){
	StoreData(Move,0,0,0,0,0);
}
static MoveData *CreateNewData(){
	MoveData *M=(MoveData*)malloc(sizeof(MoveData));
	if (! M){perror("Out of memory! Aborting..."); exit(10);}
	return M;
}
static char FlipColor(char color){
	if(color=='b'){
		return 'w';
	}else{
		return 'b';
	}
}

static PieceData *ConvertBoard(){
	int i,j;
	PieceData *Arr = malloc(sizeof(PieceData)*8*8);
	if (!Arr){perror("Out of memory! Aborting..."); exit(10);}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			(Arr[i+j*8]).value=Board[i][j].value;
			(Arr[i+j*8]).color=Board[i][j].color;
		}
	}
	return Arr;
}	
static PieceData *Dynamic(int x,int y){
	PieceData *i = malloc(sizeof(PieceData)*8*8);
	if (!i){perror("Out of memory! Aborting..."); exit(10);}
	return i;
}
static MoveData *EvaluateMove1(MoveData *MoveData_1,char color,PieceData *Temp){	//takes in the best possible moves you can make and the color making the move
	char Opposite_Color = FlipColor(color);				
	int *movement = malloc(sizeof(int)*4);
	movement[0]=(int)MoveData_1->Move_1[0];
	movement[1]=(int)MoveData_1->Move_1[1];
	movement[2]=(int)MoveData_1->Move_1[2];
	movement[3]=(int)MoveData_1->Move_1[3];
	AIMovement(movement,Temp); 			//performs your best posible moves on that board
	MoveData *MoveData_2=CreateNewData();				//create data to store your stuff
	EvaluateBestMove(Temp,MoveData_2,Opposite_Color);		//evaluate best 3 possible moves they can make
	free(movement);
return MoveData_2;							//return the 3
}
static MoveData *EvaluateMove2(MoveData *MoveData_1,char color,PieceData *Temp){	//takes in the best possible moves you can make
	char Opposite_Color = FlipColor(color);
	int *movement = malloc(sizeof(int)*4);
	movement[0]=(int)MoveData_1->Move_2[0];
	movement[1]=(int)MoveData_1->Move_2[1];
	movement[2]=(int)MoveData_1->Move_2[2];
	movement[3]=(int)MoveData_1->Move_2[3];
	AIMovement(movement,Temp); 			//performs your best posible moves on that board
	MoveData *MoveData_2=CreateNewData();				//create data to store your stuff
	EvaluateBestMove(Temp,MoveData_2,Opposite_Color);		//evaluate best 3 possible moves they can make
	free(movement);
return MoveData_2;							//return the 3
}
static MoveData *EvaluateMove3(MoveData *MoveData_1,char color,PieceData *Temp){	//takes in the best possible moves you can make and the color making the move
	char Opposite_Color = FlipColor(color);				
	int *movement = malloc(sizeof(int)*4);
	movement[0]=(int)MoveData_1->Move_3[0];
	movement[1]=(int)MoveData_1->Move_3[1];
	movement[2]=(int)MoveData_1->Move_3[2];
	movement[3]=(int)MoveData_1->Move_3[3];
	AIMovement(movement,Temp); 				//performs your best posible moves on that board
	MoveData *MoveData_2=CreateNewData();				//create data to store your stuff
	EvaluateBestMove(Temp,MoveData_2,Opposite_Color);		//evaluate best 3 possible moves they can make
	free(movement);
return MoveData_2;							//return the 3
}
static void CopyBoard2(PieceData *New, PieceData *Old){ //malloc sizeofpiecedata*64
        int x=0;
        int y=0;
        for(x=0;x<8;x++){
                for(y=0;y<8;y++){
                        New[x+8*y].value=Old[x+8*y].value;
                        New[x+8*y].color=Old[x+8*y].color;
			New[x+8*y].BoardValue=Old[x+8*y].BoardValue;

                        assert(New[x+8*y].value <= 50);
                        assert(New[x+8*y].color == 'b' || New[x+8*y].color == 'w' || New[x+8*y].color == ' ');
                }   
        }   
}
static int TakeDifferences(int *Data1, MoveData *Data2, MoveData *Data3,MoveData *Data4, MoveData *Data5){
		int *Difference=malloc(sizeof(int)*9);
		Difference[0]=Move1Parameter*Data1[4]-Move2Parameter*Data2->Move_1[4]+Move3Parameter*Data3->Move_1[4];
		Difference[1]=Move1Parameter*Data1[4]-Move2Parameter*Data2->Move_1[4]+Move3Parameter*Data3->Move_2[4];
		Difference[2]=Move1Parameter*Data1[4]-Move2Parameter*Data2->Move_1[4]+Move3Parameter*Data3->Move_3[4];
		Difference[3]=Move1Parameter*Data1[4]-Move2Parameter*Data2->Move_2[4]+Move3Parameter*Data4->Move_1[4];
		Difference[4]=Move1Parameter*Data1[4]-Move2Parameter*Data2->Move_2[4]+Move3Parameter*Data4->Move_2[4];
		Difference[5]=Move1Parameter*Data1[4]-Move2Parameter*Data2->Move_2[4]+Move3Parameter*Data4->Move_3[4];
		Difference[6]=Move1Parameter*Data1[4]-Move2Parameter*Data2->Move_3[4]+Move3Parameter*Data5->Move_1[4];
		Difference[7]=Move1Parameter*Data1[4]-Move2Parameter*Data2->Move_3[4]+Move3Parameter*Data5->Move_2[4];
		Difference[8]=Move1Parameter*Data1[4]-Move2Parameter*Data2->Move_3[4]+Move3Parameter*Data5->Move_3[4];
	int i= FindBestDifference(Difference,9);	
	free(Difference);
	return i;
}
static void ConvertBoard2D(PieceData N[8][8],PieceData *T){
	int i=0;
	int j=0;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			N[i][j].value=T[i+8*j].value;
			N[i][j].color=T[i+8*j].color;
			N[i][j].BoardValue=T[i+8*j].BoardValue;
		}
	}
}
static void PreventBug(int *move){
	char *MoveFrom=malloc(sizeof(char)*3);
	char *MoveTo=malloc(sizeof(char)*3);
	int legal=0;
	if(move[0] == 0 && move[1]==0 && move[2]==0 &&move[3]==0){
		while(legal!=1){
			int x=rand() % 7;
			int y=rand() % 7;
			int i=rand() % 7;
			int j=rand() % 7;
                        ConvertXY(x,y,MoveFrom);                //convert format
                        ConvertXY(i,j,MoveTo);                  //convert format
			legal = LegalMoveChecker(Board,MoveFrom,MoveTo,DefaultColor,1);
			if(legal==1){
				move[0]=x;
				move[1]=y;
				move[2]=i;
				move[3]=j;
			}
		}
	}
	free(MoveFrom);
	free(MoveTo);
}
