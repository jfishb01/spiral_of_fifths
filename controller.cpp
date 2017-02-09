#include "controller.h"

/**
 * Constructor to set the MIDI message for the controller
 *
 * @params int midiMessage The value of the MIDI message
 *
 * @return void 
 */
Controller::Controller(int midiMessage) {
  this->midiMessage = midiMessage;
}

/**
 * Constructor to set the MIDI message and controller number for the controller
 *
 * @params int midiMessage      The value of the MIDI message
 * @params int controllerNumber The number of the MIDI controller
 *
 * @return void 
 */
Controller::Controller(int midiMessage, int controllerNumber) {
  this->midiMessage = midiMessage;
  this->controllerNumber = controllerNumber;
}

/**
 * Get the MIDI controller number
 *
 * @return int The MIDI controller number 
 */
int Controller::getControllerNumber() {
  return this->controllerNumber;
}

/**
 * Get the MIDI message
 *
 * @params int channel The channel in use to generate the MIDI message
 *
 * @return int The MIDI message
 */
int Controller::getMidiMessage(int channel) {
  return this->midiMessage + channel;
}

