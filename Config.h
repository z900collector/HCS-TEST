#ifndef __CONFIG_HDR__
#define __CONFIG_HDR__

const int MAX_DIGITAL_INPUTS=13;
const int MAX_NAME_SIZE=8;
const int MAX_PIN_COUNT=13;


/*
 * Switch IO Module
 */
const int DEBOUNCE_DELAY=15;


/*
 * Relay IO Module
 */
const int MIN_ON_TIME=60;	// minimum time to turn on a relay for a light
const int MIN_OFF_WAIT_TIME=15;	// time after turning off a relay that we decide we reset back to normal time delays

const int DEF_RETRIGGER_TIME = 60;
const int DEF_ON_TIMER_TIME = 60;

enum STATES {OFF_STATE, ON_STATE, RETRIGGER };


typedef unsigned long uint32;
typedef unsigned int  uint16;
typedef unsigned char uint8;

#endif
