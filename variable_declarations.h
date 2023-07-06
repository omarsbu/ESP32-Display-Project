#ifndef VARIABLE_DECLARATIONS_H
#define VARIABLE_DECLARATIONS_H

/*-------------------- libraries --------------------*/
#include <Arduino.h>
#include <String.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2lib.h>
#include <esp32-hal-timer.h>
#include <Keypad.h>
#include <DHT.h>
#include <esp_task_wdt.h>
#include "bit_maps.h"
/*---------------------------------------------------*/

/*-------------------- Hardware Parameters --------------------*/
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 32     // OLED display height, in pixels
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  
/*-------------------------------------------------------------*/

/*-------------------- External Hardware --------------------*/
extern Adafruit_SSD1306 display;
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2_display;  
extern DHT dht;
extern Keypad _keypad;
/*-----------------------------------------------------------*/

/*-------------------- ESP32 Configurations --------------------*/
extern const int watchdogTimeoutMs;  
//extern hw_timer_t* timer;
//extern portMUX_TYPE timerMux;
/*--------------------------------------------------------------*/

/*-------------------- Clock Variables --------------------*/
extern int clock_hours;
extern int clock_minutes;
extern bool clock_am_pm;
extern String clock_string;
/*---------------------------------------------------------*/

/*-------------------- Temperature Variables --------------------*/
extern float humidity;
extern float temp_fah;
extern float temp_cel;
extern String temperature_string;
/*---------------------------------------------------------------*/

/*-------------------- Alarm Variables --------------------*/
extern int alarm_hours;
extern int alarm_minutes;
extern bool alarm_am_pm;
extern String alarm_string;
/*---------------------------------------------------------*/

/*-------------------- Keypad Setup --------------------*/
extern char input_character;
extern String keypad_buffer;
extern const int rowPin1;
extern const int rowPin2;
extern const int rowPin3;
extern const int rowPin4;
extern const int columnPin1;
extern const int columnPin2;
extern const int columnPin3;
extern const int columnPin4;
extern byte rowPins[4];
extern byte colPins[4];
extern const char hexaKeys[4][4];
/*------------------------------------------------------*/

/*-------------------- Flags and Temporary Variables --------------------*/
extern bool keypad_interrupt;
extern bool alarm_interrupt;
//extern bool timer_interrupt;
extern bool reset_interrupt;
extern bool main_menu;
extern String temp_string;
extern int temp_int;
/*-----------------------------------------------------------------------*/

/*---------------------------- Finite State Machines ----------------------------*/
enum menu_state {clock_menu_state, temperature_menu_state, alarm_menu_state};
extern menu_state current_menu_state;

enum display_state {clock_display_state, temperature_display_state, alarm_display_state};
extern display_state current_display_state;
/*-------------------------------------------------------------------------------*/

#endif  // VARIABLE_DECLARATIONS_H
