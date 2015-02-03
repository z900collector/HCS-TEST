#ifndef _HDR_STATEMACHINE_
#define _HDR_STATEMACHINE_

class StateMachine
{
public:
	StateMachine() {};
	virtual ~StateMachine() {};
	virtual void init()=0;
	virtual void run()=0;
	virtual int  getState()=0;
	virtual void Timer1sec()=0;
	virtual void Timer1ms()=0;
};
#endif
