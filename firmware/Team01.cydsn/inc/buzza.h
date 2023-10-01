#ifndef BUZZA_H_
#define BUZZA_H_

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

#define BUZZA_SONG_TO_PLAY					  BUZZA_NOKIA_RINGTONE

#define BUZZA_TEMPO							  320

#define BUZZA_US_IN_S						  1000000
#define BUZZA_US_IN_MS						  1000

#define BUZZA_FIND_NOTE_ARRAY_SIZE(arrayName) sizeof(arrayName) / sizeof(arrayName[0])
#define BUZZA_SONG(songName)				  songName, BUZZA_FIND_NOTE_ARRAY_SIZE(songName)

typedef struct BuzzaNote
{
	int16 noteFrequency;
	int8 noteType;
} BuzzaNote;

// TODO: MIDI to buzza

static BuzzaNote BUZZA_HAPPY_BIRTHDAY[]
	= {
		  // Score available at https://musescore.com/user/8221/scores/26906
		  { BUZZA_NOTE_C4, 4 },
		  { BUZZA_NOTE_C4, 8 },
		  { BUZZA_NOTE_D4, -4 },
		  { BUZZA_NOTE_C4, -4 },
		  { BUZZA_NOTE_F4, -4 },
		  { BUZZA_NOTE_E4, -2 },
		  { BUZZA_NOTE_C4, 4 },
		  { BUZZA_NOTE_C4, 8 },
		  { BUZZA_NOTE_D4, -4 },
		  { BUZZA_NOTE_C4, -4 },
		  { BUZZA_NOTE_G4, -4 },
		  { BUZZA_NOTE_F4, -2 },
		  { BUZZA_NOTE_C4, 4 },
		  { BUZZA_NOTE_C4, 8 },
		  { BUZZA_NOTE_C5, -4 },
		  { BUZZA_NOTE_A4, -4 },
		  { BUZZA_NOTE_F4, -4 },
		  { BUZZA_NOTE_E4, -4 },
		  { BUZZA_NOTE_D4, -4 },
		  { BUZZA_NOTE_AS4, 4 },
		  { BUZZA_NOTE_AS4, 8 },
		  { BUZZA_NOTE_A4, -4 },
		  { BUZZA_NOTE_F4, -4 },
		  { BUZZA_NOTE_G4, -4 },
		  { BUZZA_NOTE_F4, -2 },
	  };

static BuzzaNote BUZZA_MERRY_CHRISTMAS[] = {
	{ BUZZA_NOTE_C5, 4 }, // 1
	{ BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_F5, 8 }, { BUZZA_NOTE_G5, 8 }, { BUZZA_NOTE_F5, 8 }, { BUZZA_NOTE_E5, 8 },
	{ BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_D5, 4 },
	{ BUZZA_NOTE_G5, 4 }, { BUZZA_NOTE_G5, 8 }, { BUZZA_NOTE_A5, 8 }, { BUZZA_NOTE_G5, 8 }, { BUZZA_NOTE_F5, 8 },
	{ BUZZA_NOTE_E5, 4 }, { BUZZA_NOTE_C5, 4 }, { BUZZA_NOTE_C5, 4 },
	{ BUZZA_NOTE_A5, 4 }, { BUZZA_NOTE_A5, 8 }, { BUZZA_NOTE_AS5, 8 }, { BUZZA_NOTE_A5, 8 }, { BUZZA_NOTE_G5, 8 },
	{ BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_C5, 8 }, { BUZZA_NOTE_C5, 8 },
	{ BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_G5, 4 }, { BUZZA_NOTE_E5, 4 },
	{ BUZZA_NOTE_F5, 2 }, { BUZZA_NOTE_C5, 4 },
	{ BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_F5, 4 }, // 17
	{ BUZZA_NOTE_E5, 2 }, { BUZZA_NOTE_E5, 4 },
	{ BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_E5, 4 }, { BUZZA_NOTE_D5, 4 },
	{ BUZZA_NOTE_C5, 2 }, { BUZZA_NOTE_A5, 4 },
	{ BUZZA_NOTE_AS5, 4 }, { BUZZA_NOTE_A5, 4 }, { BUZZA_NOTE_G5, 4 },
	{ BUZZA_NOTE_C6, 4 }, { BUZZA_NOTE_C5, 4 }, { BUZZA_NOTE_C5, 8 }, { BUZZA_NOTE_C5, 8 },
	{ BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_G5, 4 }, { BUZZA_NOTE_E5, 4 },
	{ BUZZA_NOTE_F5, 2 }, { BUZZA_NOTE_C5, 4 },
	{ BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_F5, 8 }, { BUZZA_NOTE_G5, 8 }, { BUZZA_NOTE_F5, 8 }, { BUZZA_NOTE_E5, 8 },
	{ BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_D5, 4 },
	{ BUZZA_NOTE_G5, 4 }, { BUZZA_NOTE_G5, 8 }, { BUZZA_NOTE_A5, 8 }, { BUZZA_NOTE_G5, 8 }, { BUZZA_NOTE_F5, 8 }, // 27
	{ BUZZA_NOTE_E5, 4 }, { BUZZA_NOTE_C5, 4 }, { BUZZA_NOTE_C5, 4 },
	{ BUZZA_NOTE_A5, 4 }, { BUZZA_NOTE_A5, 8 }, { BUZZA_NOTE_AS5, 8 }, { BUZZA_NOTE_A5, 8 }, { BUZZA_NOTE_G5, 8 },
	{ BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_C5, 8 }, { BUZZA_NOTE_C5, 8 },
	{ BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_G5, 4 }, { BUZZA_NOTE_E5, 4 },
	{ BUZZA_NOTE_F5, 2 }, { BUZZA_NOTE_C5, 4 },
	{ BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_F5, 4 },
	{ BUZZA_NOTE_E5, 2 }, { BUZZA_NOTE_E5, 4 },
	{ BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_E5, 4 }, { BUZZA_NOTE_D5, 4 },
	{ BUZZA_NOTE_C5, 2 }, { BUZZA_NOTE_A5, 4 }, // 36
	{ BUZZA_NOTE_AS5, 4 }, { BUZZA_NOTE_A5, 4 }, { BUZZA_NOTE_G5, 4 },
	{ BUZZA_NOTE_C6, 4 }, { BUZZA_NOTE_C5, 4 }, { BUZZA_NOTE_C5, 8 }, { BUZZA_NOTE_C5, 8 },
	{ BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_G5, 4 }, { BUZZA_NOTE_E5, 4 },
	{ BUZZA_NOTE_F5, 2 }, { BUZZA_NOTE_C5, 4 },
	{ BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_F5, 8 }, { BUZZA_NOTE_G5, 8 }, { BUZZA_NOTE_F5, 8 }, { BUZZA_NOTE_E5, 8 },
	{ BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_D5, 4 },
	{ BUZZA_NOTE_G5, 4 }, { BUZZA_NOTE_G5, 8 }, { BUZZA_NOTE_A5, 8 }, { BUZZA_NOTE_G5, 8 }, { BUZZA_NOTE_F5, 8 },
	{ BUZZA_NOTE_E5, 4 }, { BUZZA_NOTE_C5, 4 }, { BUZZA_NOTE_C5, 4 },
	{ BUZZA_NOTE_A5, 4 }, { BUZZA_NOTE_A5, 8 }, { BUZZA_NOTE_AS5, 8 }, { BUZZA_NOTE_A5, 8 }, { BUZZA_NOTE_G5, 8 }, // 45
	{ BUZZA_NOTE_F5, 4 }, { BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_C5, 8 }, { BUZZA_NOTE_C5, 8 },
	{ BUZZA_NOTE_D5, 4 }, { BUZZA_NOTE_G5, 4 }, { BUZZA_NOTE_E5, 4 },
	{ BUZZA_NOTE_F5, 2 }

};
static BuzzaNote BUZZA_NOKIA_RINGTONE[] = {
	// Score available at https://musescore.com/user/29944637/scores/5266155
	{ BUZZA_NOTE_E5, 8 },
	{ BUZZA_NOTE_D5, 8 },
	{ BUZZA_NOTE_FS4, 4 },
	{ BUZZA_NOTE_GS4, 4 },
	{ BUZZA_NOTE_CS5, 8 },
	{ BUZZA_NOTE_B4, 8 },
	{ BUZZA_NOTE_D4, 4 },
	{ BUZZA_NOTE_E4, 4 },
	{ BUZZA_NOTE_B4, 8 },
	{ BUZZA_NOTE_A4, 8 },
	{ BUZZA_NOTE_CS4, 4 },
	{ BUZZA_NOTE_E4, 4 },
	{ BUZZA_NOTE_A4, 2 },
};

/**
 * @brief BLOCKING call to play all notes in note array
 * @param notes the array of BuzzaNotes
 * @param noteArraySize the amount of notes in the array (USE MACRO)
 */
void Buzza_play_song(BuzzaNote notes[], uint16 noteArraySize);

/**
 * @brief Plays a single frequency at a specified duration (in ms)
 * @param frequency frequency IN HZ
 * @param duration duration IN MS
 */
void Buzza_play_tone(int16 frequency, float duration);

#endif