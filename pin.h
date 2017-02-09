/**
 * Pin Class for an Arduino pin
 */

#ifndef PIN_H   /* Include guard */
#define PIN_H

#include <stddef.h>
#include <stdlib.h>
#include "midi_property.h"
#include "note.h"
#include "controller.h"

const int MAX_ANALOG_RANGE = 1023;
const int DEFAULT_VALUE = 0;

class Pin {
  public:
    // Initialize the pin with its pin number, whether or not its digital, and a reference to its associated MIDI property
    void initialize(int pinNumber, bool isDigital, MidiProperty * property);
    // Get the pin number
    int getPinNumber();
    // Get the pin's value
    int getValue();
    // Set the pin's value
    void setValue(int value);
    // Has the pin's value been changed
    bool isChanged();
    // Is the pin a digital pin
    bool isDigital();
    // Get the associated MIDI property to the pin
    MidiProperty * getMidiProperty();  
  
  private:
    int pinNumber; // The pin number
    bool isPinDigital; // Is the pin digital
    int value; // The pin value
    bool isPinChanged; // Has the pin value been changed
    MidiProperty * midiProperty; // The associated MIDI property
};


#endif // PIN_H

