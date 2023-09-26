#include "buzza.h"
#include "project.h"

void Sfx_scream()
{
	while (1)
	{
		Buzzer_Write(1);
		CyDelay(100);
		Buzzer_Write(0);
		CyDelay(100);
	}
}

void Buzzer_play_song(int16 notes[], uint16 noteArraySize)
{ // there are two values per note (pitch and duration), so for each note there are four bytes
	uint16 totalNotes = noteArraySize / 2;
	// this calculates the duration of a whole note in ms
	int wholenote1 = (60000 * 4) / BUZZA_TEMPO;
	int divider = 0, noteDuration = 0;
	for (int thisNote = 0; thisNote < totalNotes * 2; thisNote = thisNote + 2)
	{
		// calculates the duration of each note
		divider = notes[thisNote + 1];
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
		Buzzer_play_tone(notes[thisNote], noteDuration * 0.9);
		// Wait for the specief duration before playing the next note.
		CyDelay(noteDuration);
		// stop the waveform generation before the next note.
	}
}

void Buzzer_play_tone(int16 frequency, float duration)
{
	float periodS = 1 / ((float)frequency);
	float periodUs = periodS * 1000000;
	int iterations = 0;
	float maxIterations = (duration * 1000) / periodUs; // duration in ms
	while (iterations <= maxIterations)
	{
		Buzzer_Write(1);
		CyDelayUs(periodUs / 2);
		Buzzer_Write(0);
		CyDelayUs(periodUs / 2);
		iterations++;
	}
	Buzzer_Write(0);
}
