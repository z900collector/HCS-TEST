#ifndef _HDR_RELAY_
#define _HDR_RELAY_

#include "IODevice.h"
#include "Config.h"

class Relay : public IODevice
{
public:
	Relay(int pin);
	Relay(char * name,int pin);
	virtual ~Relay();
	void setName(char *name);
	void setPin(int pin);
	char * getName();
	int  getPin();
	void Timer1sec();
	void Timer1ms();
	bool isOn();
	bool isOff();
        void ON();
        void OFF();
private:
	int _pin;
	int _raw_state;
	int _last_state;
	char _name[MAX_NAME_SIZE];
	int _on_timer;
	int _off_timer;
};

#endif
