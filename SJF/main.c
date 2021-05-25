#include <stdio.h>
#include <stdlib.h>
#include "sjf.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	ProcessList pl = newProcessList(10);
	addCProcess(pl,1,0,6,0,0);
	displayProcess(pl->pl[0]);
	addCProcess(pl,2,0,8,0,0);
	displayProcess(pl->pl[1]);
	addCProcess(pl,3,0,7,0,0);
	displayProcess(pl->pl[2]);
	addCProcess(pl,4,0,3,0,0);
	displayProcess(pl->pl[3]);

	ProcessList pl1 = newProcessList(10);
	addCProcess(pl1,1,1,2,0,0);
//	displayProcess(pl->pl[0]);
	addCProcess(pl1,2,4,3,0,0);
//	displayProcess(pl->pl[1]);
	addCProcess(pl1,3,4,2,0,0);
//	displayProcess(pl->pl[2]);
	
	


	displayProcessList(pl);
	printf("		STARTING Processes\n\n");
	
	processSJF(pl);
	processSJF(pl1);
	


	destroyProcessList(&pl);
	destroyProcessList(&pl1);

	return 0;
}
