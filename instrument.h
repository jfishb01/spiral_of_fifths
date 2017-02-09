/**
 * Instrument class which performs the bulk of the logic. Uses the updated pin states to update the instrument 
 * state and send all relevant MIDI messages
 */

#ifndef INSTRUMENT_H   /* Include guard */
#define INSTRUMENT_H

#include <stddef.h>
#include <stdlib.h>
#include "pin.h"
#include "Arduino.h"
#include "midi_consts.h"

// Instrument pin constants
const int NUM_PINS = 64;
const int NUM_PINS_USED = 45;
const int OCTAVE_UP_PIN = 0;
const int OCTAVE_DOWN_PIN = 1;
const int TRANSPOSE_PIN = 2;
const int VELOCITY_PIN = 3;
const int CHANNEL_CHANGE_PIN = 4;
const int PITCH_BEND_PIN = 5;
const int VOLUME_PIN = 6;
const int MOD_PIN = 7;
const int SUSTAIN_PIN = 8;

// Instrument specific constants
const int NUM_CHANNELS = 16;
const int MAX_OCTAVE_SHIFT_DOWN = -3; // We are limited to one less downshift because of the octave shift from the transpose state
const int MAX_OCTAVE_SHIFT_UP = 4;
const int DEFAULT_CHANNEL = 0;
const int DEFAULT_OCTAVE_SHIFT = 0;


class Instrument {
  public:
    // Constructor: Set default values and initialize all provided pins with notes and controllers
    Instrument(Pin * pins);
    // Use the pins array to take action on all updated pin values by either outputting MIDI data or updating the instrument state
    void play(Pin * pins);
  
  private:
    bool isTranspose; // Is the instrument in transpose mode
    int channel; // MIDI channel for the instrument
    int velocity; // Note velocity applied universally to the instrument (individual notes are not velocity sensitive)
    int volume; // Volume for the instrument
    int octaveShift; // The number of octaves the instrument has been shifted up or down

    // Initialize all the pins with notes and controllers
    void initializePins(Pin * pins);
    // Perform the appropriate pin action by updating pin state and sending necessary MIDI messages
    void resolveAction(Pin pin);
    // Shift the instrument one octave up
    void setOctaveUp(bool isOctaveUpReleased);
    // Shift the instrument one octave down
    void setOctaveDown(bool isOctaveDownReleased);
    // Toggle the instrument transpose state
    void setTranspose(bool isTransposeReleased);
    // Set the instrument's universal note velocity
    void setVelocity(int value);
    // Set the instrument channel
    void setChannel(int value);
    // Set the instrument pitch bend
    void setPitchBend(Controller * controller, int value);
    // Set the instrument pitch bend
    void setVolume(Controller * controller, int value);
    // Set the instrument modulation
    void setModulation(Controller * controller, int value);
    // Toggle the instrument sustation mode
    void setSustain(Controller * controller, int state);
    // Toggle a note on or off
    void setNote(Note * note, bool value);
    // Send a note on MIDI message
    void noteOn(Note * note);
    // Send a not off MIDI message
    void noteOff(Note * note);
    // Send a channel wide all notes off MIDI message
    void allNotesOff();
    // Send a controller action message
    void sendControllerAction(Controller * controller, int scaledValue);
    // Fit the value to the range by scaling with the provided values
    int fitToRange(int value, int minValue, int maxValue);
};

#endif // INSTRUMENT_H

