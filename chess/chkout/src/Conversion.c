#include "Conversion.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "FileIO.h"
void CopyBoard(PieceData New[8][8], PieceData Old[8][8]){ //malloc sizeofpiecedata*64
        int x=0;
        int y=0;
        for(x=0;x<8;x++){
                for(y=0;y<8;y++){
                        New[x][y].value=Old[x][y].value;
                        New[x][y].color=Old[x][y].color;
                        assert(New[x][y].value <= 50);
                        assert(New[x][y].color == 'b' || New[x][y].color == 'w' || New[x][y].color == ' ');
                }   
        }   
    
}

/*int ConvertInputX(char position[2]){
	int i;
        char* pos[]  = {"a1","a2","a3","a4","a5","a6","a7","a8",
		        "b1","b2","b3","b4","b5","b6","b7","b8",
			"c1","c2","c3","c4","c5","c6","c7","c8",
			"d1","d2","d3","d4","d5","d6","d7","d8",
			"e1","e2","e3","e4","e5","e6","e7","e8",
			"f1","f2","f3","f4","f5","f6","f7","f8",
			"g1","g2","g3","g4","g5","g6","g7","g8",
			"h1","h2","h3","h4","h5","h6","h7","h8"};
	int number[]= {0,1,2,3,4,5,6,7};
	for(i=0;i<8;i++){
	//	if(strcmp(pos[i],position[0])==0){
		if(*(pos[0]+i) == position[0]){
			return number[i];
		}
	}
	return 7;
}
*/
int ConvertInputX(char position[2]){
	int i;
	char pos[8]= {'A','B','C','D','E','F','G','H'};
	int number[8]= {0,1,2,3,4,5,6,7};
	for(i=0;i<8;i++){
		if(pos[i]==position[0]){
			return number[i];
		}
	}
	return 2;
}
/*int ConvertInputY(char position[2]){
	int i;
        char* pos[]  = {"a1","a2","a3","a4","a5","a6","a7","a8",
		        "b1","b2","b3","b4","b5","b6","b7","b8",
			"c1","c2","c3","c4","c5","c6","c7","c8",
			"d1","d2","d3","d4","d5","d6","d7","d8",
			"e1","e2","e3","e4","e5","e6","e7","e8",
			"f1","f2","f3","f4","f5","f6","f7","f8",
			"g1","g2","g3","g4","g5","g6","g7","g8",
			"h1","h2","h3","h4","h5","h6","h7","h8"};
	int number[]= {1,2,3,4,5,6,7,8};
	for(i=0;i<8;i++){
	//	if(strcmp((pos[i]+1),position[1]) ==0){
		if(*(pos[2]+i) == position[1]){
			return number[i];
		}
	}
<<<<<<< Conversion.c
	return 7;
=======
	return 100;
}*/
int ConvertInputY(char position[2]){
	int i;
        char pos[8]= {'1','2','3','4','5','6','7','8'};
        int number[8]= {0,1,2,3,4,5,6,7};
	for(i=0;i<8;i++){
		if(pos[i]==position[1]){
                        return number[i];
		}
        }
	return 1000;
}

void ConvertXY(int x, int y, char *position){
	char *check;
/*	char *pos[]  = {"A1","A2","A3","A4","A5","A6","A7","A8",
			"B1","B2","B3","B4","B5","B6","B7","B8",
			"C1","C2","C3","C4","C5","C6","C7","C8",
			"D1","D2","D3","D4","D5","D6","D7","D8",
			"E1","E2","E3","E4","E5","E6","E7","E8",
			"F1","F2","F3","F4","F5","F6","F7","F8",
			"G1","G2","G3","G4","G5","G6","G7","G8",
			"H1","H2","H3","H4","H5","H6","H7","H8"}; */
	if(x==0&& y ==0){
		check ="A1";
	}else if(x==1 && y==0){
		check ="B1";
	}else if(x==2 && y==0){
		check ="C1";
	}else if(x==3 && y==0){
		check="D1";
	}else if(x==4 && y==0){
		check="E1";
	}else if(x==5 && y==0){
		check="F1";
	}else if(x==6 && y==0){
		check="G1";
	}else if(x==7 && y==0){
		check="H1";
	}else if(x==0 && y == 1){
                check ="A2";
        }else if(x==1 && y==1){
                check ="B2";
        }else if(x==2 && y==1){
                check ="C2";
        }else if(x==3 && y==1){
                check="D2";
        }else if(x==4 && y==1){
                check="E2";
        }else if(x==5 && y==1){
                check="F2";
        }else if(x==6 && y==1){
                check="G2";
        }else if(x==7 && y==1){
                check="H2";
        }else if(x==0 && y ==2){
                check ="A3";
        }else if(x==1 && y==2){
                check ="B3";
        }else if(x==2 && y==2){
                check ="C3";
        }else if(x==3 && y==2){
                check="D3";
        }else if(x==4 && y==2){
                check="E3";
        }else if(x==5 && y==2){
                check="F3";
        }else if(x==6 && y==2){
                check="G3";
        }else if(x==7 && y==2){
                check="H3";
        }else if(x==0&& y ==3){
                check="A4";
        }else if(x==1 && y==3){
                check="B4";
        }else if(x==2 && y==3){
                check="C4";
        }else if(x==3 && y==3){
                check="D4";
        }else if(x==4 && y==3){
                check="E4";
        }else if(x==5 && y==3){
                check="F4";
        }else if(x==6 && y==3){
                check="G4";
        }else if(x==7 && y==3){
                check="H4";
        }else if(x==0&& y==4){
                check ="A5";
        }else if(x==1 && y==4){
                check ="B5";
        }else if(x==2 && y==4){
                check ="C5";
        }else if(x==3 && y==4){
                check="D5";
        }else if(x==4 && y==4){
                check="E5";
        }else if(x==5 && y==4){
                check="F5";
        }else if(x==6 && y==4){
                check="G5";
        }else if(x==7 && y==4){
                check="H5";
        }else if(x==0&& y ==5){
                check ="A6";
        }else if(x==1 && y==5){
                check ="B6";
        }else if(x==2 && y==5){
                check ="C6";
        }else if(x==3 && y==5){
                check="D6";
        }else if(x==4 && y==5){
                check="E6";
        }else if(x==5 && y==5){
                check="F6";
        }else if(x==6 && y==5){
                check="G6";
        }else if(x==7 && y==5){
                check="H6";
        }else if(x==0&& y ==6){
                check ="A7";
        }else if(x==1 && y==6){
                check ="B7";
        }else if(x==2 && y==6){
                check ="C7";
        }else if(x==3 && y==6){
                check="D7";
        }else if(x==4 && y==6){
                check="E7";
        }else if(x==5 && y==6){
                check="F7";
        }else if(x==6 && y==6){
                check="G7";
        }else if(x==7 && y==6){
                check="H7";
        }else if(x==0&& y ==7){
                check ="A8";
        }else if(x==1 && y==7){
                check ="B8";
        }else if(x==2 && y==7){
                check ="C8";
        }else if(x==3 && y==7){
                check="D8";
        }else if(x==4 && y==7){
                check="E8";
        }else if(x==5 && y==7){
                check="F8";
        }else if(x==6 && y==7){
                check="G8";
        }else if(x==7 && y==7){
                check="H8";
        }else{
		check=NULL;
	}	
	strcpy(position, check);
}
static char *ReturnLastMoveFrom(){
	char *Last;
	Last=LastLog();
	if(Last==NULL){
		return NULL;
	}
	char *Data=malloc(sizeof(char)*2);
	if(Last[0]=='A'){
		Data[0]=Last[5];
		Data[1]=Last[6];
	}else if(Last[0]== 'P'){
		Data[0]=Last[12];
		Data[1]=Last[13];
	}else{
		return NULL;
	}
	free(Last);
	return Data;
}	

static char *ReturnLastMoveTo(){
	char *Last;
	Last=LastLog();
	if(Last==NULL){
		return NULL;
	}
	char *Data=malloc(sizeof(char)*2);
	if(Last[0]=='A'){
		Data[0]=Last[8];
		Data[1]=Last[9];
	}else if(Last[0]== 'P'){
		Data[0]=Last[15];
		Data[1]=Last[16];
	}else{
		return NULL;
	}
	free(Last);
	return Data;
}

int *ReturnData(){
	int i;
	int *Data = malloc(sizeof(int)*5);
	char *X=ReturnLastMoveFrom();
	char *Y=ReturnLastMoveTo();
	if(X==NULL || Y==NULL){
		for(i=0;i<4;i++){
			Data[i]=0;
		}
		return Data;
	}
	int X0=ConvertInputX(X);
	int Y0=ConvertInputY(X);
	int X1=ConvertInputX(Y);
	int Y1=ConvertInputY(Y);
	free(X);
	free(Y);
	Data[0]=X0;
	Data[1]=Y0;
	Data[2]=X1;
	Data[3]=Y1;
	return Data;
}
