#include "handlers.h"

void handle_change_direction(char *token)
{

    if (token != NULL)
    {
        if (strcmp(token, "F") == 0)
        {
            set_direction(FORWARD);
        }
        else if (strcmp(token, "R") == 0)
        {
            set_direction(REVERSE);
        }
    }
}

void handle_change_speed(char *token)
{
    uint8_t percent = atoi(token);
    usb_put_string(token);
    set_speed(percent);
}