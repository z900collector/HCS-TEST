/*
 * I/O Controller Module
 *
 * Controller.cpp
 * Perform system init() and create all objects.
 *
 * 2014-12-01 Sid Young
 *
 */


#include "Controller.h"
#include "Vector.h"
#include "Switch.h"
#include "Relay.h"
#include "SMBackDoor.h"


/*==================== Constructors and Destructors ==================== */


Controller::Controller() {}
Controller::~Controller(){}



/*==================== methods ==================== */



/*----------------------------------------
 *
 * init()
 *
 * Initialize the IO subsystem
 */
void Controller::init()
{
	Serial.println("Controller::init()");
	inputs.push_back( new Switch("TD1",0));  // thermal detector 1
	inputs.push_back( new Switch("TD2",1));  // thermal detector 2
	inputs.push_back( new Switch("TD3",2));  // thermal detector 3
	inputs.push_back( new Switch("BD1",3));  // deck light 1 on/off switch
	inputs.push_back( new Switch("GL1",4));  // garden light on/off switch
	inputs.push_back( new Switch("ALL",5));  // Push button "ALL" lights on switch.

	outputs.push_back( new Relay("FL1",13));	// Flood Light 1
	outputs.push_back( new Relay("FL2",12));	// Flood Light 2
	outputs.push_back( new Relay("GL1",11));	// Garden Lights 1
	outputs.push_back( new Relay("BD1",10));	// Back Deck Lights

// create Statemachine object
        
	statemachines.push_back(new SMBackDoor(this));
//	statemachines.push_back(new SMAllLights(this));

	this->debugtimer=5;
}



/*----------------------------------------
 *
 * run()
 *
 * called via the "loop()" method. constantly run's.
 */
void Controller::run()
{
	for(int i=0; i<statemachines.size();i++)
	statemachines[i]->run();
}



/*----------------------------------------
 *
 * FindInputDevice()
 *
 * Scan the Vector of input devices and find
 * the matching string (device identifier).
 */
IODevice *Controller::FindInputDevice(char *dev)
{
	for(int i=0;i<inputs.size(); i++)
	{
		if(strcmp(dev,inputs[i]->getName())==0)
			return inputs[i];
	}
	return NULL;
}


IODevice *Controller::FindOutputDevice(char *dev)
{
	for(int i=0;i<outputs.size();i++)
	{
		if(strcmp(dev,outputs[i]->getName())==0)
			return outputs[i];
	} 
	return NULL;
}




/*----------------------------------------
 *
 * Timer1ms()
 *
 * 1ms Timer Entry Point
 * Called via timer loop from main module
 * Typically calls the debounce methods in the input objects
 */
void Controller::Timer1ms()
{
	for(int i=0;i<inputs.size(); i++)
		inputs[i]->Timer1ms();
	for(int i=0;i<outputs.size(); i++)
		outputs[i]->Timer1ms();
	for(int i=0;i<statemachines.size(); i++)
		statemachines[i]->Timer1ms();
}



/*----------------------------------------
 *
 * Timer1sec()
 *
 * 1 second Timer Entry Point
 * Called via timer loop from main module
 */
void Controller::Timer1sec()
{
	for(int i=0;i<inputs.size(); i++)
		inputs[i]->Timer1sec();
	for(int i=0;i<outputs.size(); i++)
		outputs[i]->Timer1sec();
	for(int i=0;i<statemachines.size(); i++)
		statemachines[i]->Timer1sec();

	--this->debugtimer;
	if(this->debugtimer==0)
	{
		this->DumpInputs();
		this->debugtimer=5;
	}
}


/*----------------------------------------
 *
 * DumpInputs()
 *
 *
 */
void Controller::DumpInputs()
{
	for(int i=0; i<inputs.size(); i++)
	{
		Serial.print("Switch Input [");
		Serial.print(inputs[i]->getPin(), DEC );
		Serial.print("]   State: [");
		Serial.print(inputs[i]->getState(),DEC );
		Serial.println("]");
	}
}

/*
 * End of file
 */
