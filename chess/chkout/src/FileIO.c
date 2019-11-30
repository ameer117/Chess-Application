#include "FileIO.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
void WriteLog(char *MoveFrom, char *MoveTo, int AiOrHuman){
	FILE *f;
	f = fopen("./bin/log.txt", "a+");
	assert(f != NULL);
	if (AiOrHuman == 1)
		fprintf(f, "Player 1 - ");
	else if(AiOrHuman == 0)
		fprintf(f, "AI - ");
	else if(AiOrHuman == 2)
		fprintf(f, "Player 2 - ");
	else 
		fprintf(f, "error");
	fprintf(f, "\"%s %s\"\n", MoveFrom, MoveTo);
	fclose(f);

}
void DeleteLog(){
	FILE *f;
	f = fopen("./bin/log.txt","w");
	assert(f != NULL);
	fclose(f);
}
char *LastLog(){
//	static char a[20]; //changed to malloc so we can free it right after were done
	char *a= malloc(sizeof(char)*21);
	FILE *f;
	f = fopen("./bin/log.txt", "r");
	assert(f != NULL);
	while(!feof(f)){
		fgets(a,20,f);
	}fclose(f);
	return a;
}
void UndoLog(){
	int i = 0;
	int j = 0;
	int z;
	FILE *f;
	char data[20];
	f = fopen("./bin/log.txt","r");
	assert(f != NULL);
	while (fgets(data, 50, f) != NULL){ /* finds the length of the file and stores it in the i variable */
		i++;
	}
	char log[i][20];
	while (fgets(log[j], 50, f) != NULL){ /*stores each line in the array log*/
		j++;
	}
	fclose(f);




	FILE *g=NULL;
	f = fopen("./bin/log.txt", "w");
	assert(f != NULL);
	for (z = 0; z < (j-2); z++){ /* writes everything to the log except the last line */
		fprintf(g, "%s\n", log[z]);
	}
}
void SaveGame(int mode, int level){
	FILE *f;
	int a,i,j;
	char *var=malloc(sizeof(char)*3);
	char color;
	/*      int t;
	 *              char b;*/
	f = fopen("./bin/data.txt", "w");
	assert(f != NULL);
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++){
			ConvertXY(i,j,var);
			a = ReturnPieceData(var).value;
			color = ReturnPieceData(var).color;
			/*              t = j+1;
			 *                              b = ToChar(i);*/
			fprintf(f, "%d%d%c%d%d%d\n",i,j,color,a,mode,level);
		}
	fclose(f);
	free(var);
}
char *LoadGame(){
	FILE *f;
	char a,b,c,d;
	f = fopen("./bin/data.txt", "r");
	assert(f != NULL);
	char *data = malloc(sizeof(char)*10);
	while (fgets(data, 200, f) != NULL){ /*reads a line of the file*/
		a = data[0];
		b = data[1];
		c = data[2];
		d = data[3];
		int x = a - '0';
		int y = b - '0';
		int z = d - '0';
		Board[x][y].value = z;
		Board[x][y].color = c;

	}
	fclose(f);	
	return data;
}
PieceData ReturnPieceData(char *position){
	PieceData a;
	a.color = Board[ConvertInputX(position)][ConvertInputY(position)].color;
	a.value = Board[ConvertInputX(position)][ConvertInputY(position)].value;
	return a;
}
