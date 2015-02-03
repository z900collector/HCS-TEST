# HCS
Home Control System Using Arduino Microcontrollers - Version 1.0

<h1>Introduction</h1>

This is the first draft of the code for the Arduino HCS I am constructing.
The Code is written using C++ constructs.


<h1>Theory of operation</h1>

The setup() method creates a controller object that creates all objects in the system.

The loop() method is constantly looping through the controllers run() method and additional methods as the code evolves.

In setup() we create two timer objects, one is for 1ms timing and the other is 1 second timing. 
The Controller's Timer1ms() and Timer1sec() methods are called and these call the same method names in all objects so that all objects can schedlue activity on set time boundaries.

The controller run() method calls all input, output and statemachine objects run() methods. This enable all objects to get time to do what they have to do.

The FindInputDevice() and FindOutputevice() are primarily used by statemachines to get a pointer to the required object for processing needs.

All logic is in the state machine objects, this is done to both reduce the logic to a defined object and to make new addition of new functionality easier.


<h1>Planned Enhancements to code base - Phase 1</h1>

All Input, Output and Statemachine objects will have a method to return a JSON string of their state so that a REST API call can be implemented to return state.

This means a web server could be implemented to return JSON data for the controller when called from a master node. it is envisioned that many nodes will exist in the HCS and the master will use REST to get their status.


<h1>Future Releases</h1>

Phase 1 is to implement local direct control from input objects only (no remote network access)
Phase 2 is to enable Intranet access to the control network using Wifi (ESP8266 at this stage).
Phase 3 should present an overall status of the house from a cloud server, this would return limited temperature/power usage information but not occupancy or security info to un-authenticated users.

<h1>Original Articles</h1>

<ul>
<li><a href="https://z900collector.wordpress.com/arduinoembedded/arduino-object-oriented-hcs-part-1/">Arduino – Object Oriented HCS – Part 1</a></li>
<li><a href="https://z900collector.wordpress.com/arduinoembedded/arduino-object-oriented-hcs-part-2/">Arduino – Object Oriented HCS – Part 2</a></li>
</ul>
