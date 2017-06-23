#ifndef _APP_H
#define _APP_H

/* Main settings */

/*comment below line for release*/
#define TESTING

#define EEPROM_DISPLAY				0

/******** MAIN CONFIGURATION ENDS ****************/

/* LCD CONFIGURATION */
#define LCD_DDR           	   		DDRC 
#define LCD_DATA_PORT          		PORTC
#define LCD_ENABLE_PIN        		PC3 
#define LCD_REGISTER_SELECT_PIN     PC2
#define DISPLAY_INIT				1
#define LCD_NSCRL					3
#define FLOAT_T0_STRING				1
#define DECIMAL_PRECISION			10

/******** LCD CONFIGURATION ENDS ****************/

/* BUZZER: CONFIGURATION */
#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1
#define OFF_TIME					100
/******** BUZZER CONFIGURATION ENDS ****************/

/* LED: CONFIGURATION */

#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0

#define OFF_TIME		100
/******** LED CONFIGURATION ENDS ****************/

/* GSM: CONFIGURATION */

#define MSG_START					""
#define MSG_END						". Automated SMS By: AEB."

#ifdef TESTING
	#define UPhNum	"9980237552"
#else
	#define UPhNum	"9036293108"
#endif

/******** ADC CONFIGURATION ENDS ****************/
#define REF_VOL_256

/******** GSM CONFIGURATION ENDS ****************/
#define GSM_GPS_DDR				DDRD
#define GSM_GPS_PORT			PORTD
#define GSM_GPS_PIN				PD7

#define GSMEn()				do {									\
								GSM_GPS_PORT &= ~_BV(GSM_GPS_PIN); 	\
								dlyms(500);						\
							} while(0)

#define PCEn()				do {									\
								GSM_GPS_PORT |= _BV(GSM_GPS_PIN);		\
								dlyms(500);						\
							} while(0)
							
#define DISPLAY_LOC
/******** EEPROM CONFIGURATION ****************/
#define EEPROM_DISPLAY		0

#endif
