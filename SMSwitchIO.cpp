/*
 * Module: Switch IO Statemachine
 *
 * Controls the activation and timing of some of the manually controlled
 * lights
 *
 * (C) Sid Young 2014
 */

#include "SMSwitchIO.h"
#include "Controller.h"
#include "Relay.h"
#include "Switch.h"



/* -------- Constructors & Destructors ------------*/

SMSwitchIO::SMSwitchIO(Controller *pCtl)
{
	Serial.println("SMSwitchIO Constructor()");
	init();
	pGardenLights= (Relay *) pCtl->FindOutputDevice("GL1");
	pBackDeckLight= (Relay *) pCtl->FindOutputDevice("BD1");
	pGLSwitch = (Switch *) pCtl->FindInputDevice("GL1");
	pBDSwitch = (Switch *) pCtl->FindInputDevice("BD1");
}

SMSwitchIO::~SMSwitchIO() {}



/*----------------------------------------
 *
 * init()
 *
 * setup the default values for everything
 */
void SMSwitchIO::init()
{
	Serial.println("SMSwitchIO::init()");
}



/*----------------------------------------
 *
 * run()
 *
 * Called constantly from controller's run() method
 * apply logic when timers and state are appropriate.
 */
void SMSwitchIO::run()
{
	switch((int)pBDSwitch->getState())
	{
		case SWOFF:
			this->pBackDeckLight->OFF();
			break;

		case SWON:
			this->pBackDeckLight->ON();
			break;

		case SWREMOTE:
			break;
		
		default:
			Serial.println("Unknown RUN state");
			break;
	}
	switch((int)pGLSwitch->getState())
	{
		case SWOFF:
			this->pGardenLights->OFF();
			break;

		case SWON:
			this->pGardenLights->ON();
			break;

		case SWREMOTE:
			break;
		
		default:
			Serial.println("Unknown RUN state");
			break;
	}
}


/*----------------------------------------
 *
 * Timer1ms()
 *
 * Called during a 1 ms timer hook from controller
 *
 */
void SMSwitchIO::Timer1ms() {}


/*----------------------------------------
 *
 * Timer1sec()
 *
 * Called during a 1 second timer hook from controller
 */
void SMSwitchIO::Timer1sec() { }




int SMSwitchIO::getState() {return 0;}

/*
 * end of file 
 */
