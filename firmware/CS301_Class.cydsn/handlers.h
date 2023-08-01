#ifndef HANDLERS_H_
#define HANDLERS_H_

#include "movement.h"
#include "commands.h"

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void handle_change_direction(char *token);
void handle_change_speed(char *token);

#endif