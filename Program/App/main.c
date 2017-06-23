#include "main.h"

extern int8u lcdptr;
char MtrReadStr[20];
	

int main(void)
{
	
	init();
	
	while (TRUE) {
		
		if(Flag.msg) {
			Flag.msg = FALSE;
			beep(1,100);
			ProRead();
			EnUARTInt();
			PCEn();
		}
		
		sleep();
	}
	return 0;
}
static void init(void)
{
	buzinit();
	beep(2,75);
	ledinit();
	lcdinit();
	uartinit();
	Flagsinit();
	GSMinit();
	tmr2init();
	DispTitle();
	EnUARTInt();
	PCEn();
	sei();
}

static void Flagsinit(void)
{
	Flag.msg = FALSE;
}
static void tmr2init(void)
{
	TCNT2   = 75;
	TIMSK   |= _BV(TOIE2);			//ENABLE OVERFLOW INTERRUPT
	TCCR2  |=  _BV(CS22) | _BV(CS21) | _BV(CS20); /* PRESCALAR BY 256 */
}

/* overflows at every 25msec */
ISR(TIMER2_OVF_vect)
{
	static int8u i,j,k;
	TCNT2 = 75;

	if (++i >= 200) i = 0;
	switch(i) {
		case 0: case 5: ledon(); break;
		case 1: case 6: ledoff(); break;
	}
	
	if (++j >= 40) {
		j = 0;
		Flag.Meas =  TRUE;
	}
}

static void DispTitle(void)
{
	lcdclr();
	lcdws("SMART ELEC METER");
}

static void ProRead(void)
{
	char gsmmsg[100];
	char UnitsConsuStr[10];
	char AmntStr[10];
	
	float MtrRead;
	float UnitsConsu;
	float Amnt;
	
	GSMEn();
	
	gsmmsg[0] = '\0';
	
	MtrRead = atof(MtrReadStr);
	UnitsConsu = MtrRead - PREVIOUS_VAL;
	Amnt = UnitsConsu * AMOUNT_PER_UNIT;
	
	ftoa(UnitsConsu, UnitsConsuStr, 1);
	ftoa(Amnt, AmntStr, 1);
	
	strcat (gsmmsg, "Meter Reading:");
	strcat (gsmmsg, MtrReadStr);
	strcat (gsmmsg, ". Units Consumed:");
	strcat (gsmmsg, UnitsConsuStr);
	strcat (gsmmsg, ". Bill Amount:");
	strcat (gsmmsg, AmntStr);
	
	GSMsndmsg(UPhNum, gsmmsg);
}
ISR (USART_RXC_vect)
{
	static int8u i;
	static int8u state = ST_NRCVD;
		
	switch (state) {
		case  ST_NRCVD: if (UDR == '<')
							state = ST_RCVD;
						break;
		case ST_RCVD:
			MtrReadStr[i++] = UDR;
			if (UDR == '>') {
				DisUARTInt();
				MtrReadStr[i-5] = '\0';
				state = ST_NRCVD;
				i =  0;
				Flag.msg = TRUE;
			}
			break;
	}
}
