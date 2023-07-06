#ifndef KEYPAD_HANDLERS_H
#define KEYPAD_HANDLERS_H

#include "variable_declarations.h"
#include "misc_functions.h"

void deleteKey();
void menuKey();
void scrollKey();
void enterKey();
void cancelKey();
void readDigit();
void decodeKeypad(char input);

#endif  // KEYPAD_HANDLERS_H
