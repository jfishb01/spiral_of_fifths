/**
 * MIDI specific constants
 */

#ifndef MIDI_CONSTS_H   /* Include guard */
#define MIDI_CONSTS_H

// MIDI messages
const int NOTEON = 0x90;
const int NOTEOFF = 0x80;
const int PITCH_BEND = 0xE0;
const int CONTROL_CHANGE = 0xB0;
const int ALL_NOTES_OFF = 0x7B;

// MIDI controller numbers
const int MOD_CONTROL = 0x01;
const int VOLUME_CONTROL = 0x07;
const int SUSTAIN_CONTROL = 0x40;

// MIDI specific constants
const int MAX_VOLUME = 127;
const int MAX_VELOCITY = 127;
const int MAX_MODULATION = 127;
const int SUSTAIN_THRESHOLD = 64;
const int MAX_PITCH_BEND = 16383;

#endif // MIDI_CONSTS_H
