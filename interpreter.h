/*
 * interpreter.h
 *
 *  Created on: 03.11.2010
 *      Author: Frank Kevin Zey
 */

#ifndef INTERPRETER_H
#define INTERPRETER_H 
 
/* Variables */
extern int stack[1024];
extern int sp;
extern int fp;
extern unsigned int *pm;
extern int pc;
extern int pmSize;
extern unsigned int instr;
extern int x[3];
extern int v[2];

/* Functions */
void exitNJVM(int value, char *con);
void push(int value);
int pop(void);
unsigned int getNextInstruction(void);
void loadFile(char *path);
void execute(int mode);
void interprete(unsigned int instruction);
void make(void);

#endif /* INTERPRETER_H */
