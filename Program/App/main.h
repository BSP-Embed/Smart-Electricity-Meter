#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define AMOUNT_PER_UNIT		2.7
#define PREVIOUS_VAL		5400


struct  {
	volatile int8u msg:1;
	volatile int8u Meas:1;
	volatile int8u Sw:1;
	volatile int8u PIR:1;

}Flag;

enum { ST_NRCVD = 0, ST_RCVD };


//FUNCTION PROTOTYPES
static	void	init		(void);
static	void 	tmr2init	(void);
static	void	Flagsinit	(void);
static	void	DispTitle	(void);
static	void	ProRead		(void);


#endif
