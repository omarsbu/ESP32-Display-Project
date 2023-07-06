#include "variable_declarations.h"
#include "misc_functions.h"
#include "keypad_handlers.h"

// Timer variables
bool timer_interrupt = false;
hw_timer_t* timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE portMUX = portMUX_INITIALIZER_UNLOCKED;

// Timer ISR
void IRAM_ATTR timerISR() {

    timer_interrupt = true;  // Set timer interrupt flag

    // update clock variables
    if (clock_minutes == 59) {
      clock_minutes = 0;
      if (clock_hours == 11) {
        clock_am_pm = !clock_am_pm;
        clock_hours++;
      } 
      else if (clock_hours == 12)
        clock_hours = 1;
      else
          clock_hours++;
    } else
        clock_minutes++;

  if (clock_hours == alarm_hours & clock_minutes == alarm_minutes & clock_am_pm == alarm_am_pm)
    alarm_interrupt = true; 
}

// Reset button ISR
void IRAM_ATTR resetISR() {
  if (main_menu == false & digitalRead(23) == LOW);
    reset_interrupt = true;  // Set reset flag to read numbers from keypad    
}

// Doorbell ISR
void IRAM_ATTR doorISR() {;}

// setup
void setup() {
  Serial.begin(9600);

  // reset pin interrupt setup
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(23, INPUT);
  attachInterrupt(23, resetISR, FALLING);

  // DHT setup
  dht.begin();
  humidity = dht.readHumidity();
  temp_cel = dht.readTemperature();
  temp_fah = dht.readTemperature(true);  
  
  // Timer setup
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &timerISR, true);
  timerAlarmWrite(timer, 60000000, true);
  timerAlarmEnable(timer);

  // Display Setup
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  u8g2_display.begin();
  menuKey();  // display main menu   
}

// main loop
void loop () {

  // Reset clock or alarm value
  if (reset_interrupt == true & main_menu == false) {
    delay(10);
    if (reset_interrupt == true) {
    switch (current_display_state) {
      case clock_display_state:
          temp_string = "  :  " + am_or_pm(clock_am_pm);
          display_time(display, temp_string);
          keypad_interrupt = true;  // set flag to read keypad data
        break;
      case temperature_display_state:
          keypad_interrupt = false;
        break;
      case alarm_display_state:
          temp_string = "  :  " + am_or_pm(alarm_am_pm);
          display_time(display, temp_string);
          keypad_interrupt = true;  // set flag to read keypad data
        break;
      default:
        keypad_interrupt = false; // clear interrupt flags
      } 
    temp_string.clear();
    reset_interrupt = false;
    }
  }
  // Update display time when interrupt flag is set
  else if (timer_interrupt == true & keypad_interrupt == false & main_menu == false) {
      clock_string = time_to_string(clock_hours, clock_minutes, clock_am_pm);
      Serial.println(clock_string);
      display_time(display, clock_string);
      timer_interrupt = false;
  }

  // Poll keypad input
  input_character = _keypad.getKey();
  if (input_character)
    decodeKeypad(input_character);  

    // Check for alarm
  if (alarm_interrupt == true) 
  {
    display_bitmap(u8g2_display, alarm_finished_bitmap);
    for(int i = 0; i < 3; i++) {
    digitalWrite(2, HIGH);
    delay(2000);
    digitalWrite(2, LOW);
    delay(2000);
    }
    alarm_interrupt = false;

    clock_string = time_to_string(clock_hours, clock_minutes, clock_am_pm);
    display_time(display, clock_string);  // update display;
  }
  else 
    digitalWrite(2, LOW);
}
