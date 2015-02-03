/*
 * Home I/O Controller Node
 *
 * <odule: Switch
 * Provide I/O (Input) services
 *
 * 2014-12-01 Sid Young
 *
 */
#include "Switch.h"
#include "Config.h"
#include "Arduino.h"


/* ==================== Constructor/Destructors ====================*/



Switch::Switch(char *name, int pin)
{
	this->setName(name);
	this->setPin(pin);
	init();
}

Switch::~Switch() {}


/* ====================  Methods ====================*/


/*----------------------------------------
 * init()
 *
 * Clear counters and set defaults
 */

void Switch::init()
{
	pinMode(this->_pin, INPUT); 
	this->_raw_state = digitalRead(this->_pin);
	this->_pin_state = digitalRead(this->_pin);
	this->_state_counter = 0;
	this->_debounce_counter=0;
}


/*----------------------------------------
 * 
 * Timer1sec()
 * 
 */ 
void Switch::Timer1sec()
{
}



/*----------------------------------------
 * 
 * Timer1ms()
 * 
 */
void Switch::Timer1ms()
{
	Debounce();
}



/*----------------------------------------
 *
 * Debounce()
 *
 * Called via 1ms timer callback method in main loop
 *
 * Debouncing:
 * - dec debounce counter.
 * - zero up time.
 * If input still bouncing, reset debounce count to max (start again).
 *
 * Stable:
 * - Inc up time.
 * - debounce counter is 0.
 * - set pin state to raw state.
 *
 */
void Switch::Debounce()
{
	if( this->_raw_state==digitalRead(this->_pin) )
	{
		if(this->_debounce_counter)
			this->_debounce_counter--;
		else
			this->_pin_state = this->_raw_state;	// time up - we are stable!
		this->_state_counter++;		// ms time we are at this state
	}
	else
	{
		this->_debounce_counter=DEBOUNCE_DELAY;	// reset delay time
		this->_raw_state=digitalRead(this->_pin);		// set pin as changed
		this->_state_counter = 0;
	}
}




int Switch::getState() { return this->_pin_state; }
char * Switch::getName() { return this->_name; }
int  Switch::getPin() { return this->_pin; }

/*----------------------------------------
 *
 * setName()
 *
 * Save the identifier for this IO device
 */
void Switch::setName(char *name)
{
	memset(this->_name,0,MAX_NAME_SIZE);
	if(strlen(name)>MAX_NAME_SIZE)
	{
		strncpy(this->_name,name,MAX_NAME_SIZE);
	}
	else
	{
		strcpy(this->_name, name);
	}
}


/*----------------------------------------
 *
 * setPin()
 * 
 * set the pin number if its in range
 */
void Switch::setPin(int pin)
{
	if(pin<(MAX_PIN_COUNT+1))
	{
		if((pin >0)||(pin==0))
			this->_pin = pin;
	}
}

/*
 * End of file
 */

