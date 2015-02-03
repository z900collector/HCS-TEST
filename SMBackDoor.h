#ifndef _HDR_SM_BACK_DOOR_
#define _HDR_SM_BACK_DOOR_

#include "StateMachine.h"
#include "Controller.h"


typedef unsigned long uint32;

class SMBackDoor : 
public StateMachine
{
public:
  SMBackDoor(Controller *p);
  virtual ~SMBackDoor();
  void init();
  void run();
  void Timer1sec();	// 1 second timer entry point
  void Timer1ms();	// 1 ms timer entry point
  int  getState();

protected:
  void setState(int s) { 
    _c_state=s;
  };

private:
  unsigned int _c_state;
  Switch *pThermalDetector1;
  Switch *pThermalDetector2;
  Switch *pThermalDetector3;
  Relay  *pBackDeckLight;
  Relay  *pFloodLight1;
  Relay  *pFloodLight2;
  Relay  *pGardenLights;

  uint32 _on_timer;		// count down timer
  uint32 _off_timer;	// count up timer
  uint32 _retrigger_timer;	// countdown timer
  uint32 _retrig_value;	// 60 sec 
  uint32 _on_timer_value;	// time to turn on by 60s
};
#endif

/*
 * end of file
 */

