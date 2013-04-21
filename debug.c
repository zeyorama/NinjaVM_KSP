/*
 *  debug.c
 *
 *  Created on: 03.11.2010
 *      Author: Frank Kevin Zey
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "makros.h"
#include "instr.h"
#include "interpreter.h"
#include "debug.h"

/* Variables */
int spd = 0;
int xI = 0;  /* Decoded immediate value */

/* Debug functions */
void inspectStack() {	
	
	spd = sp;
	printf("\nPointer ---> Index:      Value\n");
	
	while (spd >= 0) {
		
		if (spd == fp) {
		
			printf("sp, fp  --->  %04d:      xxxx\n",spd);
		
		} else if (spd == sp) {
		
			printf("sp      --->  %04d:      xxxx\n",spd);
		
		} else if (spd == fp) {
		
			printf("fp      --->  %04d:   %5d\n",spd,stack[spd]);
		
		} else {
		
			printf("              %04d:   %5d\n",spd,stack[spd]);
		
		}
		
		spd--;
	}
	
	printf("              ---- bottom of stack ----\n\n");
}

void showInstruction(int _pc) {
  xI = SIGN_EXTEND(IMMEDIATE(pm[_pc]));
  switch ((pm[_pc]&0xFF000000)>>24) {

	    case HALT :
			  printf("%04i: HALT\n",_pc);
			break;

		  case PUSHC :
			  printf("%04i: PUSHC %i\n",_pc,xI);
			break;
			
			case ADD :
			  printf("%04i: ADD\n",_pc);
			break;
			
			case SUB :
			  printf("%04i: SUB\n",_pc);
			break;
			
			case MUL :
			  printf("%04i: MUL\n",_pc);
			break;
			
			case DIV :
			  printf("%04i: DIV\n",_pc);
			break;
			
			case MOD :
			  printf("%04i: MOD\n",_pc);
			break;
			
			case RDINT :
			  printf("%04i: RDINT\n",_pc);
			break;
			
			case WRINT :
			  printf("%04i: WRINT\n",_pc);
			break;
			
			case ASF :
			  printf("%04i: ASF %i\n",_pc,xI);
			break;
			
			case RSF :
			  printf("%04i: RSF\n",_pc);
			break;
			
			case PUSHL :
			  printf("%04i: PUSHL %i\n",_pc,xI);
			break;
			
			case POPL :
			  printf("%04i: POPL %i\n",_pc,xI);
			break;
			
			case EQ :
			  printf("%04i: EQ\n",_pc);
			break;
			
			case NE :
			  printf("%04i: NE\n",_pc);
			break;
			
			case LT :
			  printf("%04i: LT\n",_pc);
			break;
			
			case LE :
			  printf("%04i: LE\n",_pc);
			break;
			
			case GT :
			  printf("%04i: GT\n",_pc);
			break;
			
			case GE :
			  printf("%04i: GE\n",_pc);
			break;
			
			case JMP :
			  printf("%04i: JMP %i\n",_pc,xI);
			break;
			
			case BRF :
			  printf("%04i: BRF %i\n",_pc,xI);
			break;
			
			case BRT :
			  printf("%04i: BRT %i\n",_pc,xI);
			break;
			
			case CALL :
			  printf("%04i: CALL %i\n",_pc,xI);
			break;
			
			case RET :
			  printf("%04i: RET\n",_pc);
			break;
			
			case DROP :
			  printf("%04i: DROP %i\n",_pc,xI);
			break;

			case PUSHR :
			  printf("%04i: PUSHR\n",_pc);
			break;

			case POPR :
			  printf("%04i: POPR\n",_pc);
			break;
			
			case DUP :
			  printf("%04i: DUP\n",_pc);
			break;
			
			case NEW :
			  printf("%04i: NEW\n",_pc);
			break;
			
			case GETF :
			  printf("%04i: GETF\n",_pc);
			break;
			
			case PUTF :
			  printf("%04i: PUTF\n",_pc);
			break;
			
			case NEWA :
			  printf("%04i: NEWA\n",_pc);
			break;
			
			case GETLA :
			  printf("%04i: GETLA\n",_pc);
			break;
			
			case GETFA :
			  printf("%04i: GETFA\n",_pc);
			break;
			
			case PUTFA :
			  printf("%04i: PUTFA\n",_pc);
			break;
			
			case PUSHN :
			  printf("%04i: PUSHN\n",_pc);
			break;
			
			case REFQE :
			  printf("%04i: REFQE\n",_pc);
			break;
			
			case REFNE :
			  printf("%04i: REFNE\n",_pc);
			break;
			
			case VMCALL :
			  printf("%04i: VMCALL %i %i\n",_pc,0x00FF0000 & xI,0x0000FFFF & xI);
			break;
			
	    default:
			  exitNJVM(-11,"Wrong typed instruction");
		}
}

