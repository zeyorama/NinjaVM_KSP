/*
 * instr.h
 *
 *  Created on: 03.11.2010
 *      Author: Frank Kevin Zey
 */

#ifndef INSTRC_H
#define INSTRC_H

#define HALT 0
#define PUSHC 1

#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6

#define RDINT	7
#define WRINT 8

#define ASF 9
#define RSF 10
#define PUSHL 11
#define POPL 12

#define EQ 13
#define NE 14
#define LT 15
#define LE 16
#define GT 17
#define GE 18

#define JMP 19
#define BRF 20
#define BRT 21

#define CALL 22
#define RET 23
#define DROP 24
#define PUSHR 25
#define POPR 26

#define DUP 27

#define NEW 28
#define GETF 29
#define PUTF 30

#define NEWA 31
#define GETLA 32
#define GETFA 33
#define PUTFA 34
#define PUSHN 35

#define REFQE 36
#define REFNE 37

#define VMCALL 38

#endif /*INSTRC_H*/
