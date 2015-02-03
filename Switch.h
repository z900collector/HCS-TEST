#ifndef __SWITCH_HDR__
#define __SWITCH_HDR__


#include "IODevice.h"
#include "Config.h"



class Switch : public IODevice
{
public:
	Switch(char *name,int pin);
	virtual ~Switch();
	void Timer1ms();	// Debounce
	void Timer1sec();
	int    getPin();
	char * getName();
	void setPin(int pin);
	void setName(char *name);
	int  getState();	// get pin state

protected:
	void init();
	void Debounce();

private:
	int _pin;
	char _name[MAX_NAME_SIZE];
	int _raw_state;
	int _pin_state;
	unsigned int _state_counter;
	unsigned int _debounce_counter;
};


#endif

