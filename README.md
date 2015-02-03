# HCS
Home Control System Using Arduino Microcontrollers - Version 1.0

Introduction

This is the first draft of the code for the Arduino HCS I am constructing.
The Code is written using C++ constructs.


Theory of operation

The setup() method creates a controller object that creates all objects in the system.

The loop() method is constantly looping through the controllers run() method and additional methods as the code evolves.

In setup() we create two timer objects, one is for 1ms timing and the other is 1 second timing. 
The Controller's Timer1ms() and Timer1sec() methods are called and these call the same method names in all objects so that all objects can schedlue activity on set time boundaries.

The controller run() method calls all input, output and statemachine objects run() methods. This enable all objects to get time to do what they have to do.

The FindInputDevice() and FindOutputevice() are primarily used by statemachines to get a pointer to the required object for processing needs.

All logic is in the state machine objects, this is done to both reduce the logic to a defined object and to make new addition of new functionality easier.


Planned Enhancements to code base - Phase 1

All Input, Output and Statemachine objects will have a method to return a JSON string of their state so that a REST API call can be implemented to return state.

This means a web server could be implemented to return JSON data for the controller when called from a master node. it is envisioned that many nodes will exist in the HCS and the master will use REST to get their status.


Future Features

Phase 1 is to implement local direct control from input objects only (no remote network access)
Phase 2 is to enable Intranet access to the control network using Wifi (ESP8266 at this stage).
Phase 3 should present an overall status of the house from a cloud server, this would return limited temperature/power usage information but not occupancy or security info to un-authenticated users.

