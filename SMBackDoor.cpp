/*
 * Module: Back Door lighting controller
 *
 * Controls the activation and timing of the back door sensor and light
 * includes retrigger timing to keep light on when sensor keeps retriggering.
 *
 * (C) Sid Young 2014 */ 


#include "SMBackDoor.h"
#include "Controller.h"


/* -------- Constructors & Destructors ------------*/

SMBackDoor::SMBackDoor(Controller *pCtl)
{
	Serial.println("SMBackDoor Constructor()");
	init();
	pThermalDetector1 = (Switch *) pCtl->FindInputDevice("TD1");
	pThermalDetector2 = (Switch *) pCtl->FindInputDevice("TD2");
	pThermalDetector3 = (Switch *) pCtl->FindInputDevice("TD3");
	pFloodLight1 = (Relay *) pCtl->FindOutputDevice("FL1");
	pFloodLight2 = (Relay *) pCtl->FindOutputDevice("FL2");
	pGardenLights= (Relay *) pCtl->FindOutputDevice("GL1");
	pBackDeckLight= (Relay *) pCtl->FindOutputDevice("BD1");
}

SMBackDoor::~SMBackDoor() {}



/*----------------------------------------
 *
 * init()
 *
 * setup the default values for everything
 */
void SMBackDoor::init()
{
	Serial.println("SMBackDoor::init()");
	_on_timer=0;
	_off_timer=0;
	_retrigger_timer=0;
	_retrig_value=DEF_RETRIGGER_TIME;
	_on_timer_value=DEF_ON_TIMER_TIME;
	this->setState(OFF_STATE);
}



/*----------------------------------------
 *
 * run()
 *
 * Called constantly from controller's run() method
 * apply logic when timers and state are appropriate.
 */
void SMBackDoor::run()
{
	switch(this->getState())
	{
		// if we are in OFF state and input is HIGH,
		// set ON_STATE true and turn ON_TIMER to MAX
		// and retrigger to 0

		case OFF_STATE:
			this->pBackDeckLight->OFF();
			if(pThermalDetector1->getState()==1)
			{
				Serial.println("Transition to ON state");
				this->setState(ON_STATE);
				this->_on_timer = this->_on_timer_value;
				_retrigger_timer = 0;
			}
			break;

		// if we are in ON state and INPUT goes low (switch off)
		// and "on" timer >0 exit

		case ON_STATE:
			pBackDeckLight->ON();
			if((pThermalDetector1->getState()== 0) && (_on_timer>0)) return;

			// if we are in ON state and
			// INPUT goes low and
			// timer == 0 and
			// retrigger ==0
			// then start retrigger timer and
			// set RETRIGGER STATE and
			// turn light OFF
			
			if((pThermalDetector1->getState()== 0) && (_on_timer==0) && (_retrigger_timer==0))
			{
				_retrigger_timer = _retrig_value;
				Serial.println("Transition to RETRIGGER state");
				this->setState(RETRIGGER);
				return;
			}
			break;

		// if we are in RETRIGGER and input = 0 and retrigger timer == 0 then OFF_STATE
		case RETRIGGER:
			if((_retrigger_timer==0)&&(pThermalDetector1->getState()== 0))
			{
				Serial.println("Transition to OFF state");
				init();
				return;
			}
			
			// if we are in RETRIGGER and sensor goes on then
			// switch on (but for longer).
			if((_retrigger_timer>0)&&(pThermalDetector1->getState()== 1))
			{
				_retrigger_timer = 0;
				_on_timer_value +=60;
				Serial.println("Transition to ON state - for longer");
				this->setState(ON_STATE);
				return;
			}
			break;
		
		default:
			Serial.println("Unknown RUN state");
			this->setState(OFF_STATE);
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
void SMBackDoor::Timer1ms() {}


/*----------------------------------------
 *
 * Timer1sec()
 *
 * Called during a 1 second timer hook from controller
 */
void SMBackDoor::Timer1sec()
{
	if(this->getState()==OFF_STATE)
		this->_off_timer++;
	else
		this->_off_timer=0;
	if(this->_on_timer>0)
		this->_on_timer--;
	if(this->_retrigger_timer>0)
		this->_retrigger_timer--;
}




int SMBackDoor::getState() { return this->_c_state;}

/*
 * end of file 
 */
