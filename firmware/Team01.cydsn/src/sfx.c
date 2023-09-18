#include "sfx.h"
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