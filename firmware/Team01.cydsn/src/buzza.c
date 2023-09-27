#include "buzza.h"
#include "project.h"

void Buzza_play_song(BuzzaNote notes[], uint16 noteArraySize)
{ // there are two values per note (pitch and duration), so for each note there are four bytes
// this calculates the duration of a whole note in ms
#define TOTAL_NOTES 60000 * 4
	int wholenote1 = (TOTAL_NOTES) / BUZZA_TEMPO;
	int divider = 0, noteDuration = 0;
	for (int thisNote = 0; thisNote < noteArraySize; ++thisNote)
	{
		// calculates the duration of each note
		divider = notes[thisNote].noteType;
		if (divider > 0)
		{
			// regular note, just proceed
			noteDuration = (wholenote1) / divider;
		}
		else if (divider < 0)
		{
			// dotted notes are represented with negative durations!!
			noteDuration = (wholenote1) / abs(divider);
			noteDuration *= 1.5; // increases the duration in half for dotted notes
		}
		// we only play the note for 90% of the duration, leaving 10% as a pause
		Buzza_play_tone(notes[thisNote].noteFrequency, noteDuration * 0.9);
		// Wait for the specief duration before playing the next note.
		CyDelay(noteDuration);
		// stop the waveform generation before the next note.
	}
}

void Buzza_play_tone(int16 frequency, float duration)
{
	float periodS = 1 / ((float)frequency);
	float periodUs = periodS * BUZZA_US_IN_S;
	float periodUsHalf = periodUs / 2;
	int iterations = 0;
	float maxIterations = (duration * BUZZA_US_IN_MS) / periodUs; // duration in ms
	while (iterations <= maxIterations)
	{
		Buzzer_Write(1);
		CyDelayUs(periodUsHalf);
		Buzzer_Write(0);
		CyDelayUs(periodUsHalf);
		iterations++;
	}
	// Make sure off after tone is played
	Buzzer_Write(0);
}
