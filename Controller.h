#ifndef __CONTROLLER_HDR__
#define __CONTROLLER_HDR__

#include <string.h>

#include "Config.h"
#include "IODevice.h"
#include "Switch.h"
#include "Relay.h"
#include "Vector.h"
#include "StateMachine.h"


class Controller
{
public:
  Controller();
  virtual ~Controller();
  
  void run();
  void init();
  void Timer1ms();
  void Timer1sec();
  IODevice * FindInputDevice(char *);
  IODevice * FindOutputDevice(char *);
  void DumpInputs();

private:
  Vector<Switch *> inputs;
  Vector<Relay *>  outputs;
  Vector<StateMachine *>  statemachines;

	uint32 debugtimer;
};
#endif
