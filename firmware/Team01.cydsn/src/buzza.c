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

void Buzzer_play_song(int16 notes[])
{
}

void Buzzer_play_tone(int16 frequency, float duration)
{
	float periodS = 1 / ((float)frequency);
	float periodUs = periodS * 1000000;
	int iterations = 0;
	float maxIterations = (duration * 1000) / periodUs; // duration in ms
	while (iterations <= duration)
	{
		Buzzer_Write(1);
		CyDelayUs(periodUs / 2);
		Buzzer_Write(0);
		CyDelayUs(periodUs / 2);
		iterations++;
	}
	Buzzer_Write(0);
}
