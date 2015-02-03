/*
 * Module: Relay Ouput Driver
 *
 * Controls the activation and timing of a relay
 *
 * (C) Sid Young 2014-2015
 */


#include "Relay.h"
#include "Config.h"
#include "Arduino.h"

/*-------------------- Constructors & Destructors --------------------*/

Relay::Relay(char *name,int pin)
{
	this->setPin(pin);
	this->setName(name);
	pinMode(pin,OUTPUT);
	this->OFF();
}




Relay::~Relay() {}

/*-------------------- Methods --------------------*/

char * Relay::getName() { return this->_name;}
int    Relay::getPin()  { return this->_pin; }


/*----------------------------------------
 * setName()
 *
 * Save the identifier for this IO device
 */
void Relay::setName(char *s)
{
	memset(this->_name,0,MAX_NAME_SIZE);
	if(strlen(s)>MAX_NAME_SIZE)
	{
		strncpy(this->_name,s,6);
	}
	else
	{
		strcpy(this->_name, s);
	}
}


/*----------------------------------------
 * setPin()
 * 
 * set the pin number if its in range
 */
void Relay::setPin(int p)
{
	if(p<(MAX_PIN_COUNT+1))
	{
		if((p >0)||(p==0))
		{
			pinMode(p, OUTPUT);
			this->_pin = p;
		}
	}
}

bool Relay::isOn()  { return (this->_last_state!=0) ? true : false; }
bool Relay::isOff() { return (this->_last_state==0) ? true : false; }


/*----------------------------------------
 *
 * Timer1sec()
 *
 * 1 second timer entry routine
 */
void Relay::Timer1sec()
{
	if(_off_timer) _off_timer++;
	if(_on_timer) _on_timer++;
}

/*----------------------------------------
 *
 * Timer1ms()
 *
 * 1ms timer entry routine - we dont need to use it
 */
void Relay::Timer1ms()
{
}



/*----------------------------------------
 *
 * ON()
 *
 * Turn pin to HIGH and set ON timers to go so it counts UP.
 */
void Relay::ON()
{
	_off_timer=0;
	_on_timer=1;
	digitalWrite(this->_pin,HIGH);
	_last_state=1;
}

void Relay::OFF()
{
	_off_timer=1;
	_on_timer=0;
	digitalWrite(this->_pin,LOW);
	_last_state=0;
}

/*
 * End of file
 */
