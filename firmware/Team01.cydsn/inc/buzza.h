#ifndef BUZZA_H_
#define BUZZA_H_

#include "common.h"
#include "cytypes.h"

// All in Hz
#define BUZZA_NOTE_B0						  31
#define BUZZA_NOTE_C1						  33
#define BUZZA_NOTE_CS1						  35
#define BUZZA_NOTE_D1						  37
#define BUZZA_NOTE_DS1						  39
#define BUZZA_NOTE_E1						  41
#define BUZZA_NOTE_F1						  44
#define BUZZA_NOTE_FS1						  46
#define BUZZA_NOTE_G1						  49
#define BUZZA_NOTE_GS1						  52
#define BUZZA_NOTE_A1						  55
#define BUZZA_NOTE_AS1						  58
#define BUZZA_NOTE_B1						  62
#define BUZZA_NOTE_C2						  65
#define BUZZA_NOTE_CS2						  69
#define BUZZA_NOTE_D2						  73
#define BUZZA_NOTE_DS2						  78
#define BUZZA_NOTE_E2						  82
#define BUZZA_NOTE_F2						  87
#define BUZZA_NOTE_FS2						  93
#define BUZZA_NOTE_G2						  98
#define BUZZA_NOTE_GS2						  104
#define BUZZA_NOTE_A2						  110
#define BUZZA_NOTE_AS2						  117
#define BUZZA_NOTE_B2						  123
#define BUZZA_NOTE_C3						  131
#define BUZZA_NOTE_CS3						  139
#define BUZZA_NOTE_D3						  147
#define BUZZA_NOTE_DS3						  156
#define BUZZA_NOTE_E3						  165
#define BUZZA_NOTE_F3						  175
#define BUZZA_NOTE_FS3						  185
#define BUZZA_NOTE_G3						  196
#define BUZZA_NOTE_GS3						  208
#define BUZZA_NOTE_A3						  220
#define BUZZA_NOTE_AS3						  233
#define BUZZA_NOTE_B3						  247
#define BUZZA_NOTE_C4						  262
#define BUZZA_NOTE_CS4						  277
#define BUZZA_NOTE_D4						  294
#define BUZZA_NOTE_DS4						  311
#define BUZZA_NOTE_E4						  330
#define BUZZA_NOTE_F4						  349
#define BUZZA_NOTE_FS4						  370
#define BUZZA_NOTE_G4						  392
#define BUZZA_NOTE_GS4						  415
#define BUZZA_NOTE_A4						  440
#define BUZZA_NOTE_AS4						  466
#define BUZZA_NOTE_B4						  494
#define BUZZA_NOTE_C5						  523
#define BUZZA_NOTE_CS5						  554
#define BUZZA_NOTE_D5						  587
#define BUZZA_NOTE_DS5						  622
#define BUZZA_NOTE_E5						  659
#define BUZZA_NOTE_F5						  698
#define BUZZA_NOTE_FS5						  740
#define BUZZA_NOTE_G5						  784
#define BUZZA_NOTE_GS5						  831
#define BUZZA_NOTE_A5						  880
#define BUZZA_NOTE_AS5						  932
#define BUZZA_NOTE_B5						  988
#define BUZZA_NOTE_C6						  1047
#define BUZZA_NOTE_CS6						  1109
#define BUZZA_NOTE_D6						  1175
#define BUZZA_NOTE_DS6						  1245
#define BUZZA_NOTE_E6						  1319
#define BUZZA_NOTE_F6						  1397
#define BUZZA_NOTE_FS6						  1480
#define BUZZA_NOTE_G6						  1568
#define BUZZA_NOTE_GS6						  1661
#define BUZZA_NOTE_A6						  1760
#define BUZZA_NOTE_AS6						  1865
#define BUZZA_NOTE_B6						  1976
#define BUZZA_NOTE_C7						  2093
#define BUZZA_NOTE_CS7						  2217
#define BUZZA_NOTE_D7						  2349
#define BUZZA_NOTE_DS7						  2489
#define BUZZA_NOTE_E7						  2637
#define BUZZA_NOTE_F7						  2794
#define BUZZA_NOTE_FS7						  2960
#define BUZZA_NOTE_G7						  3136
#define BUZZA_NOTE_GS7						  3322
#define BUZZA_NOTE_A7						  3520
#define BUZZA_NOTE_AS7						  3729
#define BUZZA_NOTE_B7						  3951
#define BUZZA_NOTE_C8						  4186
#define BUZZA_NOTE_CS8						  4435
#define BUZZA_NOTE_D8						  4699
#define BUZZA_NOTE_DS8						  4978

#define BUZZA_SONG_TO_PLAY					  BUZZA_MEGALOVANIA

#define BUZZA_TEMPO							  160

#define BUZZA_US_IN_S						  1000000
#define BUZZA_US_IN_MS						  1000

#define BUZZA_USE_BLOCKING_MODE				  Sfx_Mode_Write(1)
#define BUZZA_USE_PWM_MODE					  Sfx_Mode_Write(0)

#define BUZZA_FIND_NOTE_ARRAY_SIZE(arrayName) sizeof(arrayName) / sizeof(arrayName[0])
#define BUZZA_SONG(songName)				  songName, BUZZA_FIND_NOTE_ARRAY_SIZE(songName)

typedef struct BuzzaNote
{
	uint16 noteFrequency;
	uint16 noteType;
} BuzzaNote;

extern const BuzzaNote BUZZA_NOKIA_RINGTONE[13];
extern const BuzzaNote BUZZA_MEGALOVANIA[601];
extern const BuzzaNote BUZZA_FIREFLIES[1247];
extern const BuzzaNote BUZZA_UNKNOWN[207];
static BuzzaNote music[] = {
	{ 391, 64 },
	{ 329, 24 },
	{ 261, 8 },
	{ 329, 32 },
	{ 391, 32 },
	{ 523, 32 },
	{ 164, 32 },
	{ 659, 32 },
	{ 587, 24 },
	{ 329, 8 },
	{ 261, 32 },
	{ 293, 32 },
	{ 246, 32 },
	{ 146, 32 },
	{ 391, 32 },
	{ 391, 16 },
	{ 659, 16 },
	{ 164, 32 },
	{ 587, 16 },
	{ 523, 16 },
	{ 493, 32 },
	{ 146, 32 },
	{ 440, 32 },
	{ 493, 16 },
	{ 329, 16 },
	{ 523, 32 },
	{ 391, 32 },
	{ 329, 32 },
	{ 261, 32 },
	{ 391, 32 },
	{ 329, 24 },
	{ 261, 8 },
	{ 329, 32 },
	{ 391, 32 },
	{ 523, 32 },
	{ 164, 32 },
	{ 659, 32 },
	{ 587, 24 },
	{ 329, 8 },
	{ 261, 32 },
	{ 293, 32 },
	{ 246, 32 },
	{ 146, 32 },
	{ 391, 32 },
	{ 391, 16 },
	{ 659, 16 },
	{ 164, 32 },
	{ 587, 16 },
	{ 523, 16 },
	{ 493, 32 },
	{ 146, 32 },
	{ 440, 32 },
	{ 493, 16 },
	{ 329, 16 },
	{ 523, 32 },
	{ 391, 32 },
	{ 329, 32 },
	{ 261, 32 },
	{ 659, 32 },
	{ 659, 16 },
	{ 523, 16 },
	{ 587, 32 },
	{ 659, 32 },
	{ 659, 32 },
	{ 195, 32 },
	{ 587, 32 },
	{ 523, 16 },
	{ 493, 16 },
	{ 523, 32 },
	{ 587, 32 },
	{ 587, 32 },
	{ 146, 32 },
	{ 493, 32 },
	{ 523, 32 },
	{ 195, 32 },
	{ 391, 16 },
	{ 329, 16 },
	{ 493, 32 },
	{ 146, 32 },
	{ 440, 32 },
	{ 493, 16 },
	{ 329, 16 },
	{ 261, 32 },
	{ 261, 32 },
	{ 391, 32 },
	{ 146, 32 },
	{ 391, 32 },
	{ 391, 16 },
	{ 523, 16 },
	{ 523, 32 },
	{ 523, 32 },
	{ 493, 16 },
	{ 440, 16 },
	{ 440, 32 },
	{ 440, 32 },
	{ 587, 32 },
	{ 698, 32 },
	{ 659, 16 },
	{ 587, 16 },
	{ 523, 16 },
	{ 523, 16 },
	{ 493, 32 },
	{ 391, 32 },
	{ 523, 32 },
	{ 523, 32 },
	{ 587, 16 },
	{ 659, 16 },
	{ 698, 16 },
	{ 783, 16 },
	{ 195, 32 },
	{ 523, 48 },
	{ 587, 16 },
	{ 659, 16 },
	{ 164, 32 },
	{ 698, 16 },
	{ 587, 16 },
	{ 523, 32 },
	{ 195, 32 },
	{ 391, 48 },
	{ 329, 24 },
	{ 261, 8 },
	{ 329, 32 },
	{ 391, 32 },
	{ 523, 32 },
	{ 164, 32 },
	{ 659, 32 },
	{ 587, 24 },
	{ 329, 8 },
	{ 261, 32 },
	{ 293, 32 },
	{ 246, 32 },
	{ 146, 32 },
	{ 391, 32 },
	{ 391, 16 },
	{ 659, 16 },
	{ 164, 32 },
	{ 587, 16 },
	{ 523, 16 },
	{ 493, 32 },
	{ 146, 32 },
	{ 440, 32 },
	{ 493, 16 },
	{ 329, 16 },
	{ 523, 32 },
	{ 391, 32 },
	{ 329, 32 },
	{ 261, 32 },
	{ 391, 32 },
	{ 329, 24 },
	{ 261, 8 },
	{ 329, 32 },
	{ 391, 32 },
	{ 523, 32 },
	{ 164, 32 },
	{ 659, 32 },
	{ 587, 24 },
	{ 329, 8 },
	{ 261, 32 },
	{ 293, 32 },
	{ 246, 32 },
	{ 146, 32 },
	{ 391, 32 },
	{ 391, 16 },
	{ 659, 16 },
	{ 164, 32 },
	{ 587, 16 },
	{ 523, 16 },
	{ 493, 32 },
	{ 146, 32 },
	{ 440, 32 },
	{ 493, 16 },
	{ 329, 16 },
	{ 523, 32 },
	{ 391, 32 },
	{ 329, 32 },
	{ 261, 32 },
	{ 659, 32 },
	{ 659, 16 },
	{ 523, 16 },
	{ 587, 32 },
	{ 659, 32 },
	{ 659, 32 },
	{ 195, 32 },
	{ 587, 32 },
	{ 523, 16 },
	{ 493, 16 },
	{ 523, 32 },
	{ 587, 32 },
	{ 587, 32 },
	{ 146, 32 },
	{ 493, 32 },
	{ 523, 32 },
	{ 195, 32 },
	{ 391, 16 },
	{ 329, 16 },
	{ 493, 32 },
	{ 146, 32 },
	{ 440, 32 },
	{ 493, 16 },
	{ 329, 16 },
	{ 261, 32 },
	{ 261, 32 },
	{ 391, 32 },
	{ 146, 32 },
	{ 391, 32 },
	{ 391, 16 },
	{ 523, 16 },
	{ 523, 32 },
	{ 523, 32 },
	{ 493, 16 },
	{ 440, 16 },
	{ 440, 32 },
	{ 440, 32 },
	{ 587, 32 },
	{ 698, 32 },
	{ 659, 16 },
	{ 587, 16 },
	{ 523, 16 },
	{ 523, 16 },
	{ 493, 32 },
	{ 391, 32 },
	{ 523, 32 },
	{ 523, 32 },
	{ 587, 16 },
	{ 659, 16 },
	{ 698, 16 },
	{ 783, 16 },
	{ 195, 32 },
	{ 523, 48 },
	{ 587, 16 },
	{ 659, 16 },
	{ 164, 32 },
	{ 698, 16 },
	{ 587, 16 },
	{ 523, 32 },
	{ 195, 32 },
};
static BuzzaNote BUZZA_MCD[] = {
	{ BUZZA_NOTE_B5, 8 },
	{ BUZZA_NOTE_FS5, 8 },
	{ BUZZA_NOTE_B5, 8 },
	{ BUZZA_NOTE_FS5, 8 },
	{ BUZZA_NOTE_B5, 8 },

	{ 0, 128 },

	{ BUZZA_NOTE_B5, 8 },
	{ BUZZA_NOTE_FS5, 8 },
	{ BUZZA_NOTE_B5, 8 },
	{ BUZZA_NOTE_FS5, 8 },

	{ 0, 128 },

	{ BUZZA_NOTE_B5, 8 },
	{ BUZZA_NOTE_FS5, 8 },
	{ BUZZA_NOTE_B5, 8 },
	{ BUZZA_NOTE_FS5, 8 },
	{ BUZZA_NOTE_B5, 8 },
};

/**
 * @brief BLOCKING call to play all notes in note array
 * @param notes the array of BuzzaNotes
 * @param noteArraySize the amount of notes in the array (USE MACRO)
 */
void Buzza_play_song(BuzzaNote *notes, uint16 noteArraySize);

/**
 * @brief Plays a single frequency at a specified duration (in ms)
 * @param frequency frequency IN HZ
 * @param duration duration IN MS
 */
void Buzza_play_tone(int16 frequency, float duration);

/**
 * @brief Plays a pwm song at a specified sampling frequency
 * @param pwmValues the frequencies to play
 * @param pwmValuesSize the size of the sample array
 * @param sampleRate the sampling rate of the PWM file
 */
void Buzza_play_pwm(int16 *pwmValues, uint16 pwmValuesSize, uint16 sampleRate);

#endif