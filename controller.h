/**
 * MIDI Controller Class which extends the MidiProperty base class
 */

#ifndef CONTROLLER_H   /* Include guard */
#define CONTROLLER_H

#include "midi_property.h"

class Controller: public MidiProperty {
  public:
    // Constructor: Set the controller's MIDI message using the provided MIDI message value
    Controller(int midiMessage); 
    // Constructor: Set the controller's MIDI message using the provided MIDI message value and MIDI controller number
    Controller(int midiMessage, int controllerNumber);
    // Get the MIDI message of the controller using the provided channel
    int getMidiMessage(int channel);
    // Get the MIDI controller's number
    int getControllerNumber();
    
  private:
    int midiMessage; // The controller's MIDI message
    int controllerNumber; // The MIDI controller number
};

#endif // CONTROLLER_H

