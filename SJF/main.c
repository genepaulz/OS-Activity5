#include <stdio.h>
#include <stdlib.h>
#include "sjf.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int TESTSIZE = 4;
	Process p[4]={
		//id bt at wt tat
		{1,6,0,0,0},
		{2,8,0,0,0},
		{3,7,0,0,0},
		{4,3,0,0,0},
	};
	displayProcess(p[0]);
//	displayProcess(p[1]);
	displayProcess(p[2]);
//	displayProcess(p[3]);

	processSJF(p,TESTSIZE);
	
	TESTSIZE = 3;
	Process p1[3]={
		//id bt at wt tat
		{1,2,1,0,0},
		{2,3,4,0,0},
		{3,2,4,0,0}	
	};
	
	processSJFwithAT(p1,TESTSIZE);
	
	
	return 0;
}
