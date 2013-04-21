/*
 * njvm.c
 *
 *  Created on: 03.11.2010
 *      Author: Frank Kevin Zey
 */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instr.h"
#include "makros.h"
#include "njvm.h"
#include "interpreter.h"

/* Variables */
int args = 0;
boolean HELP = FALSE;
boolean VERS = FALSE;
boolean DEBUG = FALSE;
boolean DEBUGHELP = FALSE;
boolean INPUT = FALSE;
int af = -1;

/* Main */
int main(int argc, char *argv[]) {
	printf("Ninja virtual machine started\n");

  if (argc > 1) {
  
    /* Scanning program arguments */
    for (args = 1; args < argc; args++) {
      
      if (strcmp(argv[args],"--help") == 0) {
        HELP = TRUE;
      } else if (strcmp(argv[args],"--debug") == 0) {
        DEBUG = TRUE;
      } else if (strcmp(argv[args],"--version") == 0) {
        VERS = TRUE;
      } else if (strcmp(argv[args],"--debughelp") == 0) {
        DEBUGHELP = TRUE;
      } else {
        INPUT = TRUE;
        af = args;
      } 
      
    }
    
    /* Executing */
    if (VERS == TRUE) {
      printf("Actual version:%s\n",VERSNR);
      printf("\n");
    }
    if (HELP == TRUE) {
      showHelp();
      printf("\n");
    }
    if (DEBUGHELP == TRUE) {
      showDebugHelp();
      printf("\n");
    }
    if (DEBUG == TRUE) {
      if (af > 0) {
        loadFile(argv[af]);
        execute(1);
        printf("\n");
      } else {
        printf("no input file\n");
      }
    }
    if (INPUT == TRUE) {
      loadFile(argv[af]);
      execute(0);
      printf("\n");
    }
     
  /* case of no program arguments */      
	} else {
	  printf("no flag or input file\n");
	}

	printf("Ninja virtual machine stopped\n");
	return (EXIT_SUCCESS);
}

/* Printing functions */
void showHelp() {
  printf("by Frank Kevin Zey\n");
	printf("Usage: ./njvm [Option] <code file>\n");
	printf("Options:\n");
	printf(" --debug <cf> : start NJVM in debug mode\n");
	printf(" --debughelp  : start help for debug modes\n");
	printf(" --version    : show version and exit\n");
	printf(" --help       : show this help and exit\n");
}

void showDebugHelp() {
  printf("Debugger %s \nDebugger Helpfunction %s\ncopyright by Frank Kevin Zey\n\n",DEBUGVERS,DEBUGHVERS);
	printf("Usage: [Option]\n");
	printf("inspect stack : shows the current stack values\n");
	printf("list          : list the program memory (program intructions)\n");
	printf("step          : step instruction for instruction\n");
	printf("run           : close debug mode and run program\n");
	printf("quit          : cancel program and exit Ninja Virtual Machine\n");
	printf("inspect_all   : shows stack values after every step (optional)\n\n");
}

