/* Miscillaneous functions to perform redundant tasks */

#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

#include "variable_declarations.h"

// Display a time on display
void display_time(Adafruit_SSD1306& display, String time);  

// Display a bitmap on display  
void display_bitmap(U8G2_SSD1306_128X64_NONAME_F_HW_I2C screen, const unsigned char bitmap[]);  

// hour & minute integers -> string
String time_to_string(int hour, int min, bool am_pm); 

// Print important variables to serial monitor (for debugging)
void statusUpdate();  

//  am_pm bool -> string
String am_or_pm(bool am_pm);  

// Display a temperature on display
void display_temperature();  

// Display contents of keypad buffer as time
void display_buffer(String buffer, bool am_pm);

#endif
