#include <stdio.h>
#include <stdlib.h>
#include "fcfs.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	ProcessList pl = newProcessList(10);
	addCProcess(pl,1,3,4,0,0);
	addCProcess(pl,2,5,3,0,0);
	addCProcess(pl,3,0,2,0,0);
	addCProcess(pl,4,5,1,0,0);
	addCProcess(pl,5,4,3,0,0);
	displayProcessList(pl);
	printf("		STARTING Processes\n\n");
	
	processFCFS(pl);

	destroyProcessList(&pl);


	return 0;
}