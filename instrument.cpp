#include "instrument.h"

/**
 * Constructor to set default values and initialize all pins with notes and controllers
 *
 * @params Pin * pins Array of pins to initialize with notes and controllers
 *
 * @return void 
 */
Instrument::Instrument(Pin * pins) {
  this->isTranspose = false;
  this->channel = DEFAULT_CHANNEL;
  this->velocity = MAX_VELOCITY; // default to max in case this controller is not in use
  this->volume = MAX_VOLUME; // default to max in case this controller is not in use
  this->octaveShift = DEFAULT_OCTAVE_SHIFT;
  this->initializePins(pins);
}

/**
 * Initialize all the pins with notes and controllers. These pin values and note numbers 
 * are all hardcoded to allow for easy manipulation in the event of wiring errors/changes
 *
 * @params Pin * pins Array of pins to initialize with notes and controllers
 *
 * @return void 
 */
void Instrument::initializePins(Pin * pins) {
  // Initialize all instrument state specific digital pins
  pins[0].initialize(OCTAVE_UP_PIN, true, NULL);
  pins[1].initialize(OCTAVE_DOWN_PIN, true, NULL);
  pins[2].initialize(TRANSPOSE_PIN, true, NULL);
  // Initialize all instrument state specific analog pins  
  pins[3].initialize(VELOCITY_PIN, false, NULL);
  pins[4].initialize(CHANNEL_CHANGE_PIN, false, NULL);

  // Initialize all analog controllers outputting MIDI
  pins[5].initialize(PITCH_BEND_PIN, false, new Controller(PITCH_BEND));
  pins[6].initialize(VOLUME_PIN, false, new Controller(CONTROL_CHANGE, VOLUME_CONTROL));
  pins[7].initialize(MOD_PIN, false, new Controller(CONTROL_CHANGE, MOD_CONTROL)); 
  // Initialize all digital controllers outputting MIDI
  pins[8].initialize(SUSTAIN_PIN, true, new Controller(CONTROL_CHANGE, SUSTAIN_CONTROL));
  
  // Initialize all notes
  pins[9].initialize(9, true, new Note(0, 4));
  pins[10].initialize(10, true, new Note(1, 4));
  pins[11].initialize(11, true, new Note(2, 4));
  pins[12].initialize(12, true, new Note(3, 4));
  pins[13].initialize(13, true, new Note(4, 4));
  pins[14].initialize(14, true, new Note(5, 4));
  pins[15].initialize(15, true, new Note(6, 4));
  pins[16].initialize(16, true, new Note(7, 4));
  pins[17].initialize(17, true, new Note(8, 4));
  pins[18].initialize(18, true, new Note(9, 4));
  pins[19].initialize(19, true, new Note(10, 4));
  pins[20].initialize(20, true, new Note(11, 4));
  pins[21].initialize(21, true, new Note(0, 5));
  pins[22].initialize(22, true, new Note(1, 5));
  pins[23].initialize(23, true, new Note(2, 5));
  pins[24].initialize(24, true, new Note(3, 5));
  pins[25].initialize(25, true, new Note(4, 5));
  pins[26].initialize(26, true, new Note(5, 5));
  pins[27].initialize(27, true, new Note(6, 5));
  pins[28].initialize(28, true, new Note(7, 5));
  pins[29].initialize(29, true, new Note(8, 5));
  pins[30].initialize(30, true, new Note(9, 5));
  pins[31].initialize(31, true, new Note(10, 5));
  pins[32].initialize(32, true, new Note(11, 5)); 
  pins[33].initialize(33, true, new Note(0, 6));
  pins[34].initialize(34, true, new Note(1, 6));
  pins[35].initialize(35, true, new Note(2, 6));
  pins[36].initialize(36, true, new Note(3, 6));
  pins[37].initialize(37, true, new Note(4, 6));
  pins[38].initialize(38, true, new Note(5, 6));
  pins[39].initialize(39, true, new Note(6, 6));
  pins[40].initialize(40, true, new Note(7, 6));
  pins[41].initialize(41, true, new Note(8, 6));
  pins[42].initialize(42, true, new Note(9, 6));
  pins[43].initialize(43, true, new Note(10, 6));
  pins[44].initialize(44, true, new Note(11, 6));  
}


/**
 * Take an action on all updated pin values by either outputting MIDI data or updating the instrument state
 *
 * @params Pin * pins Array of pins to use to determine the appropriate instrument actions
 *
 * @return void 
 */
void Instrument::play(Pin * pins) {
  for(int i = 0; i < NUM_PINS_USED; i++) {
    if(pins[i].isChanged()) {
      resolveAction(pins[i]);
    }
  }
}

/**
 * Use the pin number to determine the appropriate action and execute it
 *
 * @params Pin pin The pin to use to determine the appropriate course of action
 *
 * @return void 
 */
void Instrument::resolveAction(Pin pin) {
  switch(pin.getPinNumber()) {
    case OCTAVE_UP_PIN:
      this->setOctaveUp(pin.getValue() == LOW);
      break;
    case OCTAVE_DOWN_PIN:
      this->setOctaveDown(pin.getValue() == LOW);
      break;
    case TRANSPOSE_PIN:
      this->setTranspose(pin.getValue() == LOW);
      break;
    case VELOCITY_PIN: // Only because of our current implementation of note velocity. Ideally this data would be attached to the note
      this->setVelocity(pin.getValue());
      break;
    case CHANNEL_CHANGE_PIN:
      this->setChannel(pin.getValue());
      break;
    case PITCH_BEND_PIN:
      this->setPitchBend((Controller *)pin.getMidiProperty(), pin.getValue());
      break;
    case VOLUME_PIN:
      this->setVolume((Controller *)pin.getMidiProperty(), pin.getValue());
      break;  
    case MOD_PIN:
      this->setModulation((Controller *)pin.getMidiProperty(), pin.getValue());
      break;
    case SUSTAIN_PIN:
      this->setSustain((Controller *)pin.getMidiProperty(), pin.getValue());
      break;
    default:
      this->setNote((Note *)pin.getMidiProperty(), pin.getValue() == HIGH);
  }
}

/**
 * Increment the octave range of the instrument
 *
 * @params bool isOctaveUpReleased Is the octave up button being released
 *
 * @return void 
 */
void Instrument::setOctaveUp(bool isOctaveUpReleased) {
  // Only increment the octave on release of the octave up button when the octave is in range
  if(isOctaveUpReleased && this->octaveShift < MAX_OCTAVE_SHIFT_UP) {
    this->allNotesOff();
    this->octaveShift++;
  }
}

/**
 * Decrement the octave range of the instrument
 *
 * @params int isOctaveDown Is the octave down button being released
 *
 * @return void 
 */
void Instrument::setOctaveDown(bool isOctaveDownReleased) {
  // Only dencrement the octave on release of the octave up button when the octave is in range
  if(isOctaveDownReleased && this->octaveShift > MAX_OCTAVE_SHIFT_DOWN) {
    this->allNotesOff();
    this->octaveShift--;
  }
}

/**
 * Toggle the transpose state
 *
 * @params bool isTransposeReleased Is the transpose state button being released
 *
 * @return void 
 */
void Instrument::setTranspose(bool isTransposeReleased) {
  if(isTransposeReleased) {
    this->allNotesOff();
    this->isTranspose = !this->isTranspose;
  }
}

/**
 * Set the velocity of the instrument. Ideally this would be on the note level but our current physical implementation doesn't allow for this
 *
 * @params int value The value of the pin
 *
 * @return void 
 */
void Instrument::setVelocity(int value) {
  this->velocity = this->fitToRange(value, 0, MAX_VELOCITY);
}

/**
 * Set the channel for the instrument
 *
 * @params int value The value of the pin
 *
 * @return void 
 */
void Instrument::setChannel(int value) {
  int newChannel = this->fitToRange(value, 0, NUM_CHANNELS - 1);
  if(this->channel != newChannel) {
    this->allNotesOff();
    this->channel = newChannel;
  }
}

/**
 * Send a pitch bend message
 *
 * @params Controller * controller The controller that the pin controls
 * @params int          value      The value of the pin
 *
 * @return void 
 */
void Instrument::setPitchBend(Controller * controller, int value) {
  int pitchBend = this->fitToRange(value, 0, MAX_PITCH_BEND);
  Serial.write(controller->getMidiMessage(this->channel));
  Serial.write(pitchBend & 0x7F);
  Serial.write((pitchBend >> 8) & 0x7F);
}

/**
 * Send a controller channel volume message
 *
 * @params Controller * controller The controller that the pin controls
 * @params int          value      The value of the pin
 *
 * @return void 
 */
void Instrument::setVolume(Controller * controller, int value) {
  this->sendControllerAction(controller, this->fitToRange(value, 0, MAX_VOLUME));
}

/**
 * Send a modulation message
 *
 * @params Controller * controller The controller that the pin controls
 * @params int          value      The value of the pin
 *
 * @return void 
 */
void Instrument::setModulation(Controller * controller, int value) {
  this->sendControllerAction(controller, this->fitToRange(value, 0, MAX_MODULATION));
}

/**
 * Send a sustain message
 *
 * @params Controller * controller The controller that the pin controls
 * @params int          state      The value of the pin
 *
 * @return void 
 */
void Instrument::setSustain(Controller * controller, int state) {
  this->sendControllerAction(controller, state * SUSTAIN_THRESHOLD);
}

/**
 * Set a note state (note on vs not off)
 *
 * @params Note * note  The note that the pin controls
 * @params bool   value The value of the pin
 *
 * @return void 
 */
void Instrument::setNote(Note * note, bool value) {
  value ? this->noteOn(note) : this->noteOff(note);
} 

/**
 * Send a note on message
 *
 * @params Note * note  The note that the pin controls
 *
 * @return void 
 */
void Instrument::noteOn(Note * note) {
  Serial.write(NOTEON + this->channel);
  Serial.write(note->getValue(this->octaveShift, this->isTranspose));
  Serial.write(this->velocity); 
}

/**
 * Send a note off message
 *
 * @params Note * note  The note that the pin controls
 *
 * @return void 
 */
void Instrument::noteOff(Note * note) {
  Serial.write(NOTEOFF + this->channel);
  Serial.write(note->getValue(this->octaveShift, this->isTranspose));
  Serial.write(0);
}

/**
 * Send a channel wide all notes off message
 *
 * @return void 
 */
void Instrument::allNotesOff() {
  Serial.write(CONTROL_CHANGE + this->channel);
  Serial.write(ALL_NOTES_OFF);
  Serial.write(0);  
}

/**
 * Send a controller action message
 *
 * @params Controller * controller  The controller that the pin controls
 * @params int          scaledValue The scaled value of the pin
 *
 * @return void 
 */
void Instrument::sendControllerAction(Controller * controller, int scaledValue) {
  Serial.write(controller->getMidiMessage(this->channel));
  Serial.write(controller->getControllerNumber());
  Serial.write(scaledValue);
}

/**
 * Fit the value to the range using the passed in scale
 *
 * @params Controller * controller  The controller that the pin controls
 * @params int          scaledValue The scaled value of the pin
 *
 * @return int the adjusted value fitted to the range 
 */
int Instrument::fitToRange(int value, int minValue, int maxValue) {
  int scaledValue = round(value * ((float)((maxValue - minValue) + 1) / (MAX_ANALOG_RANGE + 1)));
  scaledValue = scaledValue > maxValue ? maxValue : scaledValue;
  scaledValue = scaledValue < minValue ? minValue : scaledValue;
  return scaledValue;
}

