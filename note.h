/**
 * MIDI Note Class which extends the MidiProperty base class
 */

#ifndef NOTE_H   /* Include guard */
#define NOTE_H

#include "midi_property.h"

class Note: public MidiProperty {
  public:
    // Constructor: set the value and octave for the note
    Note(int value, int octave);
    // Get the MIDI value of the note using the instruments octave shift and transpose state
    int getValue(int octaveShift, bool isTranspose);
    // Is the MIDI note actively being played
    bool getIsActive();
    // Set the note state to on or off
    void setState(bool isNoteActive);
  
  private:
    int value; // 0 = C, 1 = C#, 2 = D, ... 11 = B
    int octave; // MIDI octaves 0 - 10
    bool isActive; // Is the note actively on or off
};

#endif // NOTE_H

