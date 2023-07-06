#include "misc_functions.h"

void display_time(Adafruit_SSD1306& display, String time) {
  u8g2_display.clearDisplay();
	u8g2_display.clearBuffer(); // clear the display buffer
  display.clearDisplay();
  display.setTextSize(2);  // Set text size
  display.setTextColor(SSD1306_WHITE);  // Set text color
  display.setCursor(0,0);
  display.print(time);
  display.display();
}

void display_bitmap(U8G2_SSD1306_128X64_NONAME_F_HW_I2C screen, const unsigned char bitmap[]) {
	screen.clearBuffer(); // clear the display buffer
	screen.drawXBMP(0, 0, 128, 64, bitmap); // draw the bitmap
	screen.sendBuffer(); // transfer the buffer to the display	  
}

String time_to_string(int hour, int min, bool am_pm) {
  temp_string = String(hour);
  temp_string += ":";

  if (min < 10) {
    temp_string += "0";
    temp_string += String(min);
  }
  else
    temp_string += String(min);

  temp_string += am_or_pm(am_pm);
  return temp_string;
}

void statusUpdate() {  
	// Fill in with variables being monitored
}

String am_or_pm(bool am_pm)  {
  if (am_pm == true)
    return " AM";
  else
    return " PM";
}

void display_temperature() {
  humidity = dht.readHumidity();
  temp_cel = dht.readTemperature();  // Read temperature as Celsius
  temp_fah = dht.readTemperature(true);    // Read temperature as Fahrenheit 

  if (isnan(humidity) || isnan(temp_cel) || isnan(temp_fah)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  u8g2_display.clearDisplay();
	u8g2_display.clearBuffer(); // clear the display buffer
  display.clearDisplay();
  display.setTextSize(2);  // Set text size
  display.setTextColor(SSD1306_WHITE);  // Set text color
  display.setCursor(0,0);

  temp_string = "Temp: " + String(int(temp_fah)) + " F";
  display.println(temp_string);
  display.setTextSize(2);  // Set text size

//  temp_string = "Temp: " + String(int(temp_cel)) + " C";
//  display.println(temp_string);  
  temp_string = "Hum:  " + String(int(humidity)) + " %";
  display.println(temp_string);
  
  display.display();
}

void display_buffer(String buffer, bool am_pm) {
  u8g2_display.clearDisplay();
	u8g2_display.clearBuffer(); // clear the display buffer
	temp_int = buffer.length();
        if (temp_int < 2) 
        	temp_string = buffer + ":";
        else {
        	temp_string = String(buffer[0]) + String(buffer[1]) + ":";
                for (int i = 2; i < temp_int; i++)
                  temp_string += buffer[i];
        }
            
	temp_string += am_or_pm(am_pm);
        display_time(display, temp_string);
}
