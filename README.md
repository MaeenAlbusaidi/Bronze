# Bronze Challenge

The PC control program must:
- [X] Provide the user with start and stop buttons that can be used to begin and end the buggy's run on the track.
- [X] Provide an output area that displays telemetry received from the buggy during the run.


The buggy must:
- [X] Start the run on receiving a GO command via WiFi  from the controlling PC
- [X] Stop the run on receiving a STOP command via WiFi from the controlling PC
- [X] Traverse the track twice without derailing, using the IR sensors to follow the line of the track
- [X] Pause for obstacles as detected by the US rangefinder. The stopping distance is up to you (but about 10cm is reasonable).
- [X] Report to the controlling PC when obstacles are detected and cleared (a simple "obstacle seen" message is sufficient, but you may choose to do something more details, e.g. "stopping for obstacle at 5cm distance") and (periodically) an estimate of distance travelled calculated via the wheel encoder. The reporting does not have to display within the Processing graphics window (you can use the console).

# Silver Challenge

Speed Control:
- [X]  Entering the reference speed into the GUI (should be possible to update at any time during the demo)
- [X]  A reference object placed in sight of the ultrasonic distance sensor. For the second mode, the buggy’s control strategy should be to keep a constant distance from the object (15 cm). The object is moving forward at varying speeds (no backward motion, so the buggy does not need to reverse at any point).

- [X]  The telemetry reported back to the GUI should contain the distance of the object, the current mode of control, the current reference speed, and the current speed of the buggy. 
