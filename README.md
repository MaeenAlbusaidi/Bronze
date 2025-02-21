# Bronze Challenge

The PC control program must:
- [ ] Provide the user with start and stop buttons that can be used to begin and end the buggy's run on the track.
- [ ] Provide an output area that displays telemetry received from the buggy during the run.


The buggy must:
- [ ] Start the run on receiving a GO command via WiFi  from the controlling PC
- [ ] Stop the run on receiving a STOP command via WiFi from the controlling PC
- [X] Traverse the track twice without derailing, using the IR sensors to follow the line of the track
- [X] Pause for obstacles as detected by the US rangefinder. The stopping distance is up to you (but about 10cm is reasonable).
- [ ] Report to the controlling PC when obstacles are detected and cleared (a simple "obstacle seen" message is sufficient, but you may choose to do something more details, e.g. "stopping for obstacle at 5cm distance") and (periodically) an estimate of distance travelled calculated via the wheel encoder. The reporting does not have to display within the Processing graphics window (you can use the console).


