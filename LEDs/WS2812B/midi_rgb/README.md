
### Midi-Driven WS2812B LED Strip

This is a project that uses Teensy's USB-midi capabilities to use Midi messages in order to activate WS2812B LED Strips from Ableton Live
to add dynamic lighting for backing tracks during live solo performance.

Physical Specs:
  * Single guitar pedal enclosure (125b) 
  * usb-micro input 
  * 5v DC input 
  * 3 pin JST-SM output.


#### Usage tips

1) This obviously uses Teensy for it's native midi-usb and not Arduino. My particular setup targets Teensy 3.2. USB Type MIDI must be selected in the IDE.
2) My typical use-case is a midi track that targets the "Teensy Midi" device as an output in Ableton Live.
3) Serial Monitoring is driven by a global boolean variable, gDebug. If you're having issues with the code; I suggest enabling the monitoring.


#### TODO

1) Removing the RGB LED because it detracts more than it benefits this project.
2) Re-writing the midi input system to accomodate the capabilities of a WS2812B strip.
3) Interpetting clock messages in order to make timed effects (such as a single "Knight Rider" style travelling band)
4) Rewrite README to better document how the midi input system works, and include examples.
