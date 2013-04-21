/*
 * njvm.h
 *
 *  Created on: 03.11.2010
 *      Author: Frank Kevin Zey
 */

#ifndef NJVM_H
#define NJVM_H

/* Variables */
extern int args;
extern int af;
extern boolean HELP;
extern boolean VERS;
extern boolean DEBUG;
extern boolean DEBUGHELP;
extern boolean INPUT;

/* Functions */
void showHelp(void);
void showDebugHelp(void);
int main(int argc, char *argv[]);

#endif /*NJVM_H*/
