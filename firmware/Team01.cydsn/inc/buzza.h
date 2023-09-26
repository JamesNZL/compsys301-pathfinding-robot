#ifndef BUZZA_H_
#define BUZZA_H_

#include "cytypes.h"

#define NOTE_B0								  31
#define NOTE_C1								  33
#define NOTE_CS1							  35
#define NOTE_D1								  37
#define NOTE_DS1							  39
#define NOTE_E1								  41
#define NOTE_F1								  44
#define NOTE_FS1							  46
#define NOTE_G1								  49
#define NOTE_GS1							  52
#define NOTE_A1								  55
#define NOTE_AS1							  58
#define NOTE_B1								  62
#define NOTE_C2								  65
#define NOTE_CS2							  69
#define NOTE_D2								  73
#define NOTE_DS2							  78
#define NOTE_E2								  82
#define NOTE_F2								  87
#define NOTE_FS2							  93
#define NOTE_G2								  98
#define NOTE_GS2							  104
#define NOTE_A2								  110
#define NOTE_AS2							  117
#define NOTE_B2								  123
#define NOTE_C3								  131
#define NOTE_CS3							  139
#define NOTE_D3								  147
#define NOTE_DS3							  156
#define NOTE_E3								  165
#define NOTE_F3								  175
#define NOTE_FS3							  185
#define NOTE_G3								  196
#define NOTE_GS3							  208
#define NOTE_A3								  220
#define NOTE_AS3							  233
#define NOTE_B3								  247
#define NOTE_C4								  262
#define NOTE_CS4							  277
#define NOTE_D4								  294
#define NOTE_DS4							  311
#define NOTE_E4								  330
#define NOTE_F4								  349
#define NOTE_FS4							  370
#define NOTE_G4								  392
#define NOTE_GS4							  415
#define NOTE_A4								  440
#define NOTE_AS4							  466
#define NOTE_B4								  494
#define NOTE_C5								  523
#define NOTE_CS5							  554
#define NOTE_D5								  587
#define NOTE_DS5							  622
#define NOTE_E5								  659
#define NOTE_F5								  698
#define NOTE_FS5							  740
#define NOTE_G5								  784
#define NOTE_GS5							  831
#define NOTE_A5								  880
#define NOTE_AS5							  932
#define NOTE_B5								  988
#define NOTE_C6								  1047
#define NOTE_CS6							  1109
#define NOTE_D6								  1175
#define NOTE_DS6							  1245
#define NOTE_E6								  1319
#define NOTE_F6								  1397
#define NOTE_FS6							  1480
#define NOTE_G6								  1568
#define NOTE_GS6							  1661
#define NOTE_A6								  1760
#define NOTE_AS6							  1865
#define NOTE_B6								  1976
#define NOTE_C7								  2093
#define NOTE_CS7							  2217
#define NOTE_D7								  2349
#define NOTE_DS7							  2489
#define NOTE_E7								  2637
#define NOTE_F7								  2794
#define NOTE_FS7							  2960
#define NOTE_G7								  3136
#define NOTE_GS7							  3322
#define NOTE_A7								  3520
#define NOTE_AS7							  3729
#define NOTE_B7								  3951
#define NOTE_C8								  4186
#define NOTE_CS8							  4435
#define NOTE_D8								  4699
#define NOTE_DS8							  4978

#define BUZZA_SONG_TO_PLAY					  song2

#define BUZZA_TEMPO							  200

#define BUZZA_FIND_NOTE_ARRAY_SIZE(arrayName) sizeof(arrayName) / sizeof(arrayName[0])

static int16 song1[] = {
	// Score available at https://musescore.com/user/8221/scores/26906
	NOTE_C4,
	4,
	NOTE_C4,
	8,
	NOTE_D4,
	-4,
	NOTE_C4,
	-4,
	NOTE_F4,
	-4,
	NOTE_E4,
	-2,
	NOTE_C4,
	4,
	NOTE_C4,
	8,
	NOTE_D4,
	-4,
	NOTE_C4,
	-4,
	NOTE_G4,
	-4,
	NOTE_F4,
	-2,
	NOTE_C4,
	4,
	NOTE_C4,
	8,
	NOTE_C5,
	-4,
	NOTE_A4,
	-4,
	NOTE_F4,
	-4,
	NOTE_E4,
	-4,
	NOTE_D4,
	-4,
	NOTE_AS4,
	4,
	NOTE_AS4,
	8,
	NOTE_A4,
	-4,
	NOTE_F4,
	-4,
	NOTE_G4,
	-4,
	NOTE_F4,
	-2,
};
static int16 song2[] = {
	// Score available at https://musescore.com/user/6208766/scores/1497501
	NOTE_C5, 4, // 1
	NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
	NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
	NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
	NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
	NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8,
	NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
	NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
	NOTE_F5, 2, NOTE_C5, 4, // 8
	NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
	NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
	NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
	NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
	NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8,
	NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
	NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
	NOTE_F5, 2, NOTE_C5, 4,
	NOTE_F5, 4, NOTE_F5, 4, NOTE_F5, 4, // 17
	NOTE_E5, 2, NOTE_E5, 4,
	NOTE_F5, 4, NOTE_E5, 4, NOTE_D5, 4,
	NOTE_C5, 2, NOTE_A5, 4,
	NOTE_AS5, 4, NOTE_A5, 4, NOTE_G5, 4,
	NOTE_C6, 4, NOTE_C5, 4, NOTE_C5, 8, NOTE_C5, 8,
	NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
	NOTE_F5, 2, NOTE_C5, 4,
	NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
	NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
	NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8, // 27
	NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
	NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8,
	NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
	NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
	NOTE_F5, 2, NOTE_C5, 4,
	NOTE_F5, 4, NOTE_F5, 4, NOTE_F5, 4,
	NOTE_E5, 2, NOTE_E5, 4,
	NOTE_F5, 4, NOTE_E5, 4, NOTE_D5, 4,
	NOTE_C5, 2, NOTE_A5, 4, // 36
	NOTE_AS5, 4, NOTE_A5, 4, NOTE_G5, 4,
	NOTE_C6, 4, NOTE_C5, 4, NOTE_C5, 8, NOTE_C5, 8,
	NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
	NOTE_F5, 2, NOTE_C5, 4,
	NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
	NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
	NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
	NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
	NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, // 45
	NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
	NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
	NOTE_F5, 2, NOTE_C5, 4,
	NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
	NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
	NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
	NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
	NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, // 53
	NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
	NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
	NOTE_F5, 2
};
static int16 song3[] = {
	// Score available at https://musescore.com/user/29944637/scores/5266155
	NOTE_E5,
	8,
	NOTE_D5,
	8,
	NOTE_FS4,
	4,
	NOTE_GS4,
	4,
	NOTE_CS5,
	8,
	NOTE_B4,
	8,
	NOTE_D4,
	4,
	NOTE_E4,
	4,
	NOTE_B4,
	8,
	NOTE_A4,
	8,
	NOTE_CS4,
	4,
	NOTE_E4,
	4,
	NOTE_A4,
	2,
};

void Buzzer_scream();

void Buzzer_play_song(int16 notes[], uint16 noteArraySize);

void Buzzer_play_tone(int16 frequency, float duration);

#endif