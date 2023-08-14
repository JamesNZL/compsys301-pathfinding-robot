#ifndef HANDLERS_H_
#define HANDLERS_H_

#include "commands.h"
#include "movement.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Handlers_change_direction(char *token);
void Handlers_change_speed(char *token);

#endif