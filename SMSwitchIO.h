#ifndef _HDR_SM_SWITCH_IO_
#define _HDR_SM_SWITCH_IO_

#include "StateMachine.h"
#include "Controller.h"

typedef unsigned long uint32;
enum swstates {SWOFF=0, SWON, SWREMOTE };

class SMSwitchIO : public StateMachine
{
public:
	SMSwitchIO(Controller *p);
	virtual ~SMSwitchIO();
	void init();
	void run();
	void Timer1sec();	// 1 second timer entry point
	void Timer1ms();	// 1 ms timer entry point
	int  getState();	// will do nothing in this SMachine

private:
	Relay  *pBackDeckLight;
	Switch *pBDSwitch;

	Relay  *pGardenLights;
	Switch *pGLSwitch;
};
#endif

/*
 * end of file
 */
