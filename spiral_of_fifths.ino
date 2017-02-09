/**
 * Application entry point for the Spiral of Fifths instrument
 * 
 * Sets up the Arduino and instrument. Continuously reads and updates pin states. Calls the instruments play() method.
 * 
 * Originally this was intended to perform all Arduino read/write communications and MIDI conversions. Unforunately
 * this required passing too much data around and exhausted the Arduino's memory causing SEGFAULTS. Instead I had to settle
 * for doing all Arudino write operations from the instrument class
 */

#include "spiral_of_fiths.h"

Pin pins[NUM_PINS_USED]; // All pins in use by the Arduino
Instrument * instrument; // The instrument class performing all the logic

/**
 * Iterate through all arduino pins and set the values
 *
 * @return voidm
 */
void setPinValues() {
  for(int i = 0; i < NUM_PINS_USED; i++) {
    if(pins[i].isDigital()) {
      pins[i].setValue(digitalRead(pins[i].getPinNumber()));
    } else {
      pins[i].setValue(analogRead(pins[i].getPinNumber()));
    }
  }
}

/**
 * Called upon program initialization. Instantiates the instrument, sets the baud rate, and initializes pins as inputs/outputs
 *
 * @return void
 */
void setup() {
  instrument = new Instrument(pins);

  //  Set MIDI baud rate:
  Serial.begin(57600, SERIAL_8N1);

  // Initialize all pins as inputs
  for(int i = 0; i < NUM_PINS; i++) {
     pinMode(i, INPUT);
  }
}

/**
 * Continuous program loop which sets the pin values and informs the instrument of the actions
 *
 * @return void
 */
void loop() {
  setPinValues();
  instrument->play(pins);
}

