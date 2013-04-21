/*
 * interpreter.c
 *
 *  Created on: 03.11.2010
 *      Author: Frank Kevin Zey
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"
#include "makros.h"
#include "instr.h"
#include "debug.h"

/*Exit for NJVM*/
void exitNJVM(int value, char *con) {
  if (pm!=NULL) {
    free(pm);
  }
  printf("%s\n",con);
  printf("Ninja virtual machine stopped\n");
  exit(value);
}
/* VM variables */
int r = -1;
/* Stack variables */
int stack[1024];  /* Stack */
int sp = 0;       /* Stack pointer */
int fp = 0;       /* Frame pointer */
int popvalue = 0; /* Pop Value */
/* Stack functions */
void push(int element) {  /* pushs integer on stack */
    if (sp > 1024) {      /* control, is stack full? */
      printf("Stack full, no more space\n");
      printf("Ninja Virtual Machine stopped\n");
			exit(-7);
    } else {
			stack[sp] = SIGN_EXTEND(IMMEDIATE(element));
			sp++;
    }
}

int pop() { 			        /* pops integer from stack */
    if (sp <= 0) { 				/* control, is stack empty? */
        printf("Stack empty\n");
        printf("Ninja Virtual Machine stopped\n");
				exit(-8);
    } else {
        sp--;
        popvalue = SIGN_EXTEND(IMMEDIATE(stack[sp]));
        stack[sp] = 0;
        return popvalue;
    }
}

/* File loading system variables */
FILE *pof;        /* File pointer */
int pmSize = 0;   /* Size of file and program memory */
/* File loading system functions */
void loadFile(char *path) { /* Instruction from file */
	pof = fopen(path,"r");
	if (pof == NULL) {
		printf("%s :File not found, please check program name",path);
		exitNJVM(-1,"");
	} else {
		fseek(pof, 0, SEEK_END);
		pmSize = (int) (ftell(pof) / (sizeof(unsigned int)));
		fseek(pof, 0, SEEK_SET);
		pm = (unsigned int*) malloc(pmSize * sizeof(unsigned int)); 
		if (fread(pm,sizeof(unsigned int),pmSize,pof) != pmSize) {
			printf("Error at loading file: %s",path);
			exitNJVM(-2,"");
		}
	}
	fclose(pof);
}

/* Program memory variables*/
unsigned int* pm = NULL; /* Program memory */
int pc = 0;       /* Programpointer */
/* Program memory functions */
unsigned int getNextInstruction() {
  if (pc < pmSize) {
		return pm[pc++];
	} else {
		printf("Program memory overflow\n");
		printf("Ninja Virtual Machine stopped\n");
		exit(-9);
	}
}

/* Interpreter variables */
int x[3];          /* Space for interpreted values
                      x[0] = Opcode
                      x[1] = Immediate
                      x[2] = */
/* Interpreter functions*/
void interprete(unsigned int instruction) {
  x[0] = (instruction & 0xFF000000);
	x[0] = (x[0]>>24);
	if (x[0] == VMCALL) {
		x[1] = ((instruction & 0x00FF0000)>>16);
		x[2] = (instruction & 0x0000FFFF);
	} else {
		x[1] = SIGN_EXTEND(IMMEDIATE(instruction));
	}
}

/* Executing variables */
int v[2];           /* Space for arithmetic instructions */
unsigned int instr; /* Encoded instruction */
char com;           /* Readed debug command from console */
int listIndex = 0;
int oldpc = 0;
/* Debugger variables */
boolean step = FALSE;
boolean run = FALSE;
boolean IS = FALSE; /* Inspect Stack */
boolean IA = FALSE; /* Inspect (Stack) All */
boolean quit = FALSE;
boolean list = FALSE;
void execute(int mode) {
  while (0 < 1) {
  
    /* Save old pc and decode first binary code */
    oldpc = pc;
    instr = getNextInstruction();
    interprete(instr);
    
    /* No debugger */
    if (mode == 0) {
      make();
      
    /* Debugger */
    } else if (mode == 1) {
      showInstruction(oldpc);
      printf("DEBUG: list, step, run, inspect stack, quit  -  optional inspect_all: ");
		  scanf("%s",&com);
		  
		  /* Parse debug command */
		  if (0 == strcmp("inspect", &com)) {
			  scanf("%s",&com);
			  IS = TRUE;
			  
		  } else if (0 == strcmp("inspect_all", &com)) {
			  IA = TRUE;
			  
		  } else if ((0 == strcmp("quit", &com)) || (0 == strcmp("exit",&com))) {
			  quit = TRUE;
			  
		  } else if (0 == strcmp("run", &com)) {
	  		run = TRUE;
	  		
	  	} else if (0 == strcmp("list", &com)) {
			  list = TRUE;
			  
		  } else if (0 == strcmp("step", &com)) {
        step = TRUE;
      
      /* Error wrong command */
		  } else {
		    printf("%s", &com);
			  exitNJVM(-4,": wrong typed command");
		  }
		
		/* Ispect stack all mode */  
	  } else if (mode == 2) {
	    showInstruction(oldpc);
	    make();
	    inspectStack();
	  }
	  
	  /* executing debug */
	  if (IS == TRUE) {
	    make();
			inspectStack();
			
	  } else if (run == TRUE) {
	    mode = 0;
	    pc = oldpc;
	    
	  } else if (quit == TRUE) {
	    exitNJVM(2,"Debbuger closed");
	    
	  } else if (IA == TRUE) {
	    pc = oldpc;
			mode = 2;
			continue;
			
	  } else if (list == TRUE) {
	    for (listIndex = 0; listIndex < pmSize; listIndex++) {
			  showInstruction(listIndex);
			}
			pc = oldpc;
			printf("\n");
		  continue;
		  
	  } else if (step == TRUE) {
	    make();
	  }
	  
	  /* Set debug flags to default */ 
	  step = FALSE;
    run = FALSE;
    IS = FALSE; /* Inspect Stack */
    IA = FALSE; /* Inspect (Stack) All */
    quit = FALSE;
    list = FALSE;
  }

}

void make() {
    switch (x[0]) {
      case HALT :
        free(pm);
        printf("Ninja virtual machine stopped\n");
        exit(EXIT_SUCCESS);
      break;
      
      case PUSHC :
        push(x[1]);
      break;
      
      case ADD :
        v[0] = pop();
        v[1] = pop();
        push(v[0] + v[1]);
      break;
      
      case SUB :
        v[0] = pop();
        v[1] = pop();
        push(v[1] - v[0]);
      break;
      
      case MUL :
        v[0] = pop();
        v[1] = pop();
        push(v[1] * v[0]);
      break;
      
      case DIV :
        v[0] = pop();
        v[1] = pop();
        if (v[0]!=0) {
          push((int) (v[1] / v[0]));
        } else {
          exitNJVM(-10,"Division by zero(0)");
        }
      break;
      
      case MOD :
        v[0] = pop();
        v[1] = pop();
        if (v[0] != 0) {
          push(v[1] % v[0]);
        } else {
          push(0);
        }
      break;
      
      case RDINT :
        scanf("%i",&v[0]);
				push(SIGN_EXTEND(IMMEDIATE(v[0])));
      break;
      
      case WRINT :
        v[0] = pop();
        printf("%i\n",v[0]);
      break;
      
      
      case ASF :
        if ((sp+x[1]) < 1024) {
          push(fp);
          fp = sp;
          sp = sp + x[1];
        } else {
          exitNJVM(-13,"allocate stack frame error, stack overflow");
        }
      break;
      
      case RSF :
        sp = fp;
        fp = pop();
      break;
      
      case PUSHL :
        v[0] = stack[(fp + x[1])];
        push(v[0]);
      break;
      
      case POPL :
        v[0] = pop();
        stack[fp + x[1]] = v[0];
      break;
      
      case EQ :
        v[0] = pop();
        v[1] = pop();
        if (v[1] == v[0]) {
          push(1);
        } else {
          push(0);
        }
      break;
      
      case NE :
        v[0] = pop();
        v[1] = pop();
        if (v[1] != v[0]) {
          push(1);
        } else {
          push(0);
        }
      break;
      
      case LT :
        v[0] = pop();
        v[1] = pop();
        if (v[1] < v[0]) {
          push(1);
        } else {
          push(0);
        }
      break;
      
      case LE :
        v[0] = pop();
        v[1] = pop();
        if (v[1] <= v[0]) {
          push(1);
        } else {
          push(0);
        }
      break;
      
      case GT :
        v[0] = pop();
        v[1] = pop();
        if (v[1] > v[0]) {
          push(1);
        } else {
          push(0);
        }
      break;
      
      case GE :
        v[0] = pop();
        v[1] = pop();
        if (v[1] >= v[0]) {
          push(1);
        } else {
          push(0);
        }
      break;
      
      case JMP :
        pc = x[1];
      break;
      
      case BRF : /* branch if poped value false(0) */
				v[0] = pop();
				if (v[0] == 0) {
					pc = x[1];
				} else if((v[0] != 0) && (v[0] != 1)) {
					exitNJVM(-12,"unknown boolean value");
				}
			break;
			
			case BRT : /* branch if poped value true(1) */
				v[0] = pop();
				if (v[0] == 1) {
					pc = x[1];
				} else if((v[0] != 0) && (v[0] != 1)) {
					exitNJVM(-12,"unknown boolean value");
				}
			break;
      
      case CALL :
        push(pc);
        pc = x[1];
      break;
      
      case RET :
        pc = pop();
      break;
      
      case DROP :
        sp = sp - x[1];        
      break;
      
      case PUSHR :
        push(r);
      break;
      
      case POPR :
        r = pop();
      break;
      
      case DUP :
        v[0] = pop();
        push(v[0]);
        push(v[0]);
      break;
      
      default:
        exitNJVM(-11,"Wrong instruction");
    }
}
