#include "note.h"

/**
 * Constructor to set the value and octave for the note
 *
 * @params int value  The value of the note (0 - 11)
 * @params int octave The octave of the note (0 - 10)
 *
 * @return void 
 */
Note::Note(int value, int octave) {
  this->value = value;
  this->octave = octave;
  this->isActive = false;
}

/**
 * Get the MIDI value of the note using the instruments octave shift and transpose state
 *
 * @params int octaveShift Shift the note value this many octaves (negative is a downshift)
 * @params int isTranspose Is the instrument in a transpose state
 *
 * @return int the MIDI note value 
 */
int Note::getValue(int octaveShift, bool isTranspose) {
  if(isTranspose && ((this->value % 2) == 1)) { // Shift all odd notes down an octave for transpose state
    return (this->value + (this->octave + octaveShift - 1) * 12);  
  }
  return (this->value + (this->octave + octaveShift) * 12);    
}

/**
 * Is the MIDI note actively being played
 *
 * @return bool Is the MIDI note active
 */
bool Note::getIsActive() {
  return this->isActive;
}

/**
 * Set the note state to on or off
 *
 * @return void
 */
void Note::setState(bool isNoteActive) {
  this->isActive = isNoteActive;
}


