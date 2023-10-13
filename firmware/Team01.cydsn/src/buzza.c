#include "buzza.h"
#include "project.h"
#define DURATION
// #define FAST_ISR

volatile static uint16 sample;

volatile static BuzzaNote *BUZZA_PWM_SONG;
volatile static uint16 buzzaPwmSongSize;
volatile static bool flagPause;

CY_ISR(BUZZA_CAPTURE_SAMPLE)
{
	if (flagPause)
	{
		flagPause = FALSE;
		PWM_Play_Buzzer_WriteCompare(0);
		return;
	}
	sample++;
	if (sample >= buzzaPwmSongSize)
	{
		Timer_song_sampler_Stop();
		isr_capture_sample_Stop();
	}
	else
	{
#ifdef FAST_ISR
		PWM_Play_Buzzer_WritePeriod(BUZZA_PWM_SONG[sample].noteFrequency);
		PWM_Play_Buzzer_WriteCompare(BUZZA_PWM_SONG[sample].noteFrequency >> 1);
#else
		Timer_song_sampler_Stop();
		uint16 timerPeriod = BUZZA_PWM_SONG[sample].noteType * 8 * 10;
		Timer_song_sampler_WritePeriod(timerPeriod);
		Timer_song_sampler_WriteCounter(timerPeriod);
		uint16 period = (uint32)100000 / BUZZA_PWM_SONG[sample].noteFrequency - 1;
		PWM_Play_Buzzer_WritePeriod(period);
		PWM_Play_Buzzer_WriteCompare(period >> 2);
		flagPause = TRUE;
		Timer_song_sampler_Start();
#endif
	}
}

void Buzza_play_song(BuzzaNote *notes, uint16 noteArraySize)
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

void Buzza_play_pwm(int16 *pwmValues, uint16 pwmValuesSize, uint16 sampleRate)
{
	sample = 0;
	buzzaPwmSongSize = pwmValuesSize;
	BUZZA_PWM_SONG = pwmValues;
	Timer_song_sampler_Start();
	Timer_song_sampler_WritePeriod(BUZZA_PWM_SONG[sample].noteType * 1000);
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
