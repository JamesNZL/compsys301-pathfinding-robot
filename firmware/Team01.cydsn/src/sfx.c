#include "sfx.h"
#include "project.h"
void Sfx_scream()
{
	while (1)
	{
		Buzzer_Write(1);
		CyDelay(1000);
		Buzzer_Write(0);
		CyDelay(1000);
	}
}