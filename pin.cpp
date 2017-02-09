#include "pin.h"

/**
 * Initialize an Arduino pin
 *
 * @params int            pinNumber The number of the pin on the Arduino
 * @params bool           isDigital Is this a digital pin 
 * @params MidiProperty * property  A pointer to the associated MIDI property
 *
 * @return void 
 */
void Pin::initialize(int pinNumber, bool isDigital, MidiProperty * property) {
    this->pinNumber = pinNumber;
    this->isPinDigital = isDigital;
    this->value = DEFAULT_VALUE;
    this->isPinChanged = false;
    this->midiProperty = property;
}

/**
 * Get the Arduino pin number
 *
 * @return int The pin number 
 */
int Pin::getPinNumber() {
  return this->pinNumber;
}

/**
 * Get the pin value
 *
 * @return int The pin value 
 */
int Pin::getValue() {
  return this->value; 
}

/**
 * Set the pin value
 *
 * @return void
 */
void Pin::setValue(int value) {
  this->isPinChanged = (value != this->value);
  this->value = value;
}

/**
 * Is the pin digital
 *
 * @return bool
 */
bool Pin::isDigital() {
  return this->isPinDigital;
}

/**
 * Has the pin value changed since its previous read
 *
 * @return bool
 */
bool Pin::isChanged() {
  return this->isPinChanged;
}

/**
 * Get the MIDI property associated with the pin
 *
 * @return MidiProperty * The associated MIDI property
 */
MidiProperty * Pin::getMidiProperty() {
  return this->midiProperty;
}

