#include "keypad_handlers.h"

void deleteKey() {
  if (keypad_interrupt == true) {  // check for reset flag
    temp_int = keypad_buffer.length();  

    if (keypad_buffer.length() > 0) 
      keypad_buffer.remove(temp_int - 1);  // remove last character from buffer

    // place ':' character in right position
    if (temp_int < 2)
      temp_string = keypad_buffer + ":";
    else {
        temp_string = String(keypad_buffer[0]) + String(keypad_buffer[1]) + ":";
        for(int i = 2; i < temp_int + 1; i++)
          temp_string += String(keypad_buffer[i]);
    }
    
    if (current_display_state == clock_display_state)
      temp_string += am_or_pm(clock_am_pm);
    else if (current_display_state == alarm_display_state)
      temp_string += am_or_pm(alarm_am_pm);

    display_time(display, temp_string);
  }
}
void menuKey() {
  // display clock menu screen 
  current_menu_state = clock_menu_state;
  display_bitmap(u8g2_display, clock_menu_bitmap);
  main_menu = true;
}

void scrollKey() {
  // menu screen FSM
  if (main_menu == false)
    return;

  switch (current_menu_state) {
    case clock_menu_state:
        current_menu_state = temperature_menu_state;
        display_bitmap(u8g2_display, temp_menu_bitmap);
      break;
    case temperature_menu_state:
        current_menu_state = alarm_menu_state;
        display_bitmap(u8g2_display, alarm_menu_bitmap);
      break;
    case alarm_menu_state:
        current_menu_state = clock_menu_state;
        display_bitmap(u8g2_display, clock_menu_bitmap);
      break;
    default:
      Serial.println("Error: Unkown Menu State");
  }
}

void enterKey() {
  if (keypad_interrupt == true) {  // check for reset flag
    if (keypad_buffer.length() >= 4)  {  // check number of digits entered    
    // update clock and alarm variables FSM
      switch (current_display_state) {
        case clock_display_state:
            // update clock variables
            temp_string = keypad_buffer.substring(0,2);
            clock_hours = temp_string.toInt();
            temp_string = keypad_buffer.substring(2);
            clock_minutes = temp_string.toInt();
            clock_string = time_to_string(clock_hours, clock_minutes, clock_am_pm);
            display_time(display, clock_string);  // update display
          break;
        case temperature_display_state: ;  // do nothing
          break;
        case alarm_display_state:
            // update alarm variables
            temp_string = keypad_buffer.substring(0,2);
            alarm_hours = temp_string.toInt();
            temp_string = keypad_buffer.substring(2);
            alarm_minutes = temp_string.toInt();
            alarm_string = time_to_string(alarm_hours, alarm_minutes, alarm_am_pm);
            display_time(display, alarm_string);  // update display
          break;
        default:  ;
        }       
    // clear interrupt flags and keypad buffer
      keypad_interrupt = false;
      keypad_buffer.clear();
    }
  }
  else if (main_menu == true) {  // check for menu flag

  // update display setting fsm
      switch (current_menu_state) {
        case clock_menu_state:
              current_display_state = clock_display_state;
              clock_string = time_to_string(clock_hours, clock_minutes, clock_am_pm);
              display_time(display, clock_string);  // update display
          break;
        case temperature_menu_state:
            current_display_state = temperature_display_state;
            display_temperature();
          break;
        case alarm_menu_state:
              current_display_state = alarm_display_state;
              alarm_string = time_to_string(alarm_hours, alarm_minutes, alarm_am_pm);
              display_time(display, alarm_string);  
          break;
        default:
          Serial.println("Error: Unkown Menu State");
      }  
      main_menu = false;
      keypad_interrupt = false;
  }
}
void cancelKey() {
  // return screen fsm
  if (main_menu == true)
    return;

    switch (current_display_state) {
      case clock_display_state:
          display_time(display, clock_string);  
        break;
      case temperature_display_state: 
          display_temperature();
        break;
      case alarm_display_state:
          display_time(display, alarm_string);  
        break;
      default:  ;
    } 
  
  keypad_interrupt = false;
  keypad_buffer.clear();  // Clear keypad buffer
}
void readDigit() {
  // convert buffer string to time string format
  temp_int = keypad_buffer.length();
  if(keypad_interrupt == true & temp_int < 4) {
    keypad_buffer += String(input_character);
    if (temp_int < 2) 
      temp_string = keypad_buffer + ":";
    else {
      temp_string = String(keypad_buffer[0]) + String(keypad_buffer[1]) + ":";
      for (int i = 2; i < temp_int + 1; i++)
        temp_string += keypad_buffer[i];
    }
    
  // clock or alarm 
    if (current_display_state == clock_display_state) 
      temp_string += am_or_pm(clock_am_pm);
    else if(current_display_state == alarm_display_state) 
      temp_string += am_or_pm(alarm_am_pm);
   
    display_time(display, temp_string);
  }
}
void am_pmKey() {
  if (main_menu == true)
    return;

  if (current_display_state == clock_display_state) {
  // Toggle am/pm for clock
    clock_am_pm = !clock_am_pm;
    if (reset_interrupt == false) {
      temp_string = time_to_string(clock_hours, clock_minutes, clock_am_pm);
      display_time(display, temp_string);
    }
    else 
      display_buffer(keypad_buffer, clock_am_pm);
  } 
  else if (current_display_state == alarm_display_state) {  
  // Toggle am/pm for alarm
    alarm_am_pm = !alarm_am_pm;
    if (reset_interrupt == false) {
      temp_string = time_to_string(alarm_hours, alarm_minutes, alarm_am_pm);
      display_time(display, temp_string);
    }
    else 
      display_buffer(keypad_buffer, alarm_am_pm); 
  }
}

void decodeKeypad(char input) {
  switch(input) {
    case 'A': // Delete Digit
      deleteKey();
      break;
    case 'B': // Display Menu  
      menuKey();
      break;
    case 'C': // Scroll through menu
      scrollKey();
      break;
    case 'D': // Enter keypad information
        enterKey();
      break;
    case '*':  // Cancel current task
      cancelKey();
      break;
    case '#': // Switch am->pm and pm->am
      am_pmKey();
    default: 
    readDigit();
  }
}
