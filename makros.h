/*
 * makros.h
 *
 *  Created on: 03.11.2010
 *      Author: Frank Kevin Zey
 */

#ifndef MAKROS_H
#define MAKROS_H

/* Constants */
#define VERSNR "1.4 (compiled: 06.12.2010)"
#define DEBUGVERS "1.0.1 (compiled: 06.12.2010)"
#define DEBUGHVERS "1.0.0 (compiled: 15.11.2010)"

/* Boolean */
#define boolean int
#define TRUE 1
#define FALSE 0

/* Immediate value */
#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

/* MSB bit controlls / SIZE */
#define MSB (1 << ((8 * sizeof(unsigned int)) - 1))
#define COUNT_IS_BYTES(size) (((size) & MSB) != 0)
#define COUNT_IS_OBJREFS(size) (((size) & MSB) == 0)
#define COUNT_FROM_SIZE(size) ((size) & (¬MSB))
#define OBJ_HAS_BYTES(objref) COUNT_IS_BYTES((objref) -> size)
#define OBJ_HAS_OBJREFS(objref) COUNT_IS_OBJREFS((objref) -> size)
#define COUNT_FROM_OBJREF(objref) COUNT_FROM_SIZE((objref) -> size)

#endif /* MAKROS_H */
