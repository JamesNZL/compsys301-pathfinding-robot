#include "handlers.h"

void Handlers_change_direction(char *token)
{

    if (token != NULL)
    {
        if (strcmp(token, "F") == 0)
        {
            Movement_set_direction(FORWARD);
        }
        else if (strcmp(token, "R") == 0)
        {
            Movement_set_direction(REVERSE);
        }
    }
}

void Handlers_change_speed(char *token)
{
    uint8_t percent = atoi(token);
    usb_put_string(token);
    Movement_set_speed(percent);
}