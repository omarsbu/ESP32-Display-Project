#include "variable_declarations.h"

/*-------------------- ESP32 Configurations --------------------*/
const int watchdogTimeoutMs = 10000;  
//hw_timer_t* timer = NULL;
//portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
/*--------------------------------------------------------------*/

/*-------------------- Clock Variables --------------------*/
int clock_hours = 5;
int clock_minutes = 29;
bool clock_am_pm = false;
String clock_string;
/*---------------------------------------------------------*/

/*-------------------- Temperature Variables --------------------*/
float humidity;
float temp_fah;
float temp_cel;
String temperature_string;
/*---------------------------------------------------------------*/

/*-------------------- Alarm Variables --------------------*/
int alarm_hours;
int alarm_minutes;
bool alarm_am_pm;
String alarm_string;
/*---------------------------------------------------------*/

/*--------------------------- Keypad Setup ---------------------------*/
char input_character;
String keypad_buffer;
const int rowPin1 = 13;
const int rowPin2 = 12;
const int rowPin3 = 14;
const int rowPin4 = 27;
const int columnPin1 = 26;
const int columnPin2 = 25;
const int columnPin3 = 33;
const int columnPin4 = 32;
byte rowPins[4] = {rowPin1, rowPin2, rowPin3, rowPin4};
byte colPins[4] = {columnPin1, columnPin2, columnPin3, columnPin4};
const char hexaKeys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
/*--------------------------------------------------------------------*/

/*--------------------------- External Hardware ---------------------------*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2_display(U8G2_R0, U8X8_PIN_NONE);
DHT dht(DHTPIN, DHTTYPE);
Keypad _keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, 4, 4);
/*-------------------------------------------------------------------------*/

/*-------------------- Flags and Temporary Variables --------------------*/
 bool keypad_interrupt = false;
 bool alarm_interrupt = false;
// bool timer_interrupt = false;
 bool reset_interrupt = false;
 bool main_menu = true;
 String temp_string;
 int temp_int;
/*-----------------------------------------------------------------------*/

/*-------------------------------- Finite State Machines --------------------------------*/
menu_state current_menu_state = clock_menu_state;
display_state current_display_state;
/*---------------------------------------------------------------------------------------*/
