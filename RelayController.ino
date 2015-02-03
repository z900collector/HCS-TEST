/*
 * Object Oriented I/O Controller Module
 *
 * Module: Main Entry Module
 * Create Controller object and timers,
 * call controller and methods requiring regular running.
 *
 * 2014-12-01 Sid Young
 *
 */

#include <TimerObject.h>
#include "Arduino.h"
#include "Controller.h"

Controller  *pCtl;
TimerObject *t1;
TimerObject *t2;

void setup()
{
	Serial.begin(9600);
	pCtl = new Controller();
	pCtl->init();
	t1 = new TimerObject(1);    // 1ms timer tick
	t1->setOnTimer(&Timer1ms);
	t1->Start();
	t2 = new TimerObject(1000);    // 1second timer tick
	t2->setOnTimer(&Timer1sec);
	t2->Start();
}


void loop()
{
	pCtl->run();
	t1->Update();
	t2->Update();
}



void Timer1ms()
{
	pCtl->Timer1ms();
}



void Timer1sec()
{
	Serial.println("Seconds Loop Running");
	pCtl->Timer1sec();
	//pRadio->BroadcastStatus();	// RF24 library call to send status out
}

/*
 * end of file
 */
