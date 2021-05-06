#include <stdio.h>
#include <stdlib.h>
#include "fcfs.h"
#define TESTSIZE 4
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Process p[4] = {
	//id, bt, at, wt, tat
		{1,6,0,0,0},
		{2,8,0,0,0},
		{3,7,0,0,0},
		{4,3,0,0,0},
	};

	displayProcess(p[0]);
//	displayProcess(p[1]);
	displayProcess(p[2]);
//	displayProcess(p[3]);
	
	processFCFS(p,TESTSIZE);
	
	
	

	return 0;
}
