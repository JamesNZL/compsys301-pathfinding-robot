#include "buzza.h"
#include "project.h"
#define DURATION

volatile uint16 sample;

static int16 *BUZZA_PWM_SONG;
static uint16 buzzaPwmSongSize;

CY_ISR(BUZZA_CAPTURE_SAMPLE)
{
	if (sample >= buzzaPwmSongSize)
	{
		Timer_song_sampler_Stop();
		isr_capture_sample_Stop();
	}
	else
	{
		Buzza
	}
}

void Buzza_play_song(BuzzaNote notes[], uint16 noteArraySize)
{ // there are two values per note (pitch and duration), so for each note there are four bytes
// this calculates the duration of a whole note in ms
#define BAR_DURATION 60000 * 4
	int wholenote1 = (BAR_DURATION) / BUZZA_TEMPO;
	float divider = 0, noteDuration = 0;
	for (int thisNote = 0; thisNote < noteArraySize; ++thisNote)
	{

		// calculates the duration of each note
		divider = notes[thisNote].noteType;
		if (divider > 0)
		{
			// regular note, just proceed
			noteDuration = 26 * divider;
		}
		else if (divider < 0)
		{
			// dotted notes are represented with negative durations!!
			noteDuration = (wholenote1) / abs(divider);
			noteDuration *= 1.5; // increases the duration in half for dotted notes
		}
		// we only play the note for 90% of the duration, leaving 10% as a pause
		Buzza_play_tone(notes[thisNote].noteFrequency, noteDuration);
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

void Buzza_play_pwm(int16 pwmValues[], uint16 pwmValuesSize, uint16 sampleRate)
{
	sample = 0;
	buzzaPwmSongSize = pwmValuesSize;
	BUZZA_PWM_SONG = pwmValues;
	Timer_song_sampler_Start();
	Timer_song_sampler_WritePeriod(sampleRate / 64);
	isr_capture_sample_StartEx(BUZZA_CAPTURE_SAMPLE);
	// // Take new sample every sampleRate Hz,
	// float duration = 1 / sampleRate;
	// uint16 sample;

	// for (sample; sample < sizeof(pwmValues) / sizeof(pwmValues[0]); ++sample)
	// {
	// 	Buzza_play_tone(pwmValues[sample], duration);
	// 	// CyDelayUs(duration);
	// }
}
