//display setup
//Library for the OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
//button setup
#define PIN 3				// кнопка подключена сюда (PIN --- КНОПКА --- GND)

#include "GyverButton.h"
GButton butt1(PIN);

byte mode =0;

void setup() {
  // initialize with the I2C addr 0x3C
  display.begin(i2c_Address, true); // Address 0x3C default
    // set text color
  display.setTextColor(SH110X_WHITE);
  // set text size
  display.setTextSize(1,2);
  // set text cursor position
  display.setCursor(25,0);
  // show text
  display.println("Electrocentr");
  display.setCursor(25,20);
  display.println("Hall Tester");
  display.setCursor(25,40);
  display.setTextSize(1);
  display.println("by Asyan4ik");
  display.setCursor(45,50);
  display.setTextSize(1);
  display.println("v0.1");
  delay(1000);
  display.clearDisplay();
  display.setCursor(35,25);
  display.setTextSize(1);
  display.println("Press button");


  //button settings
    butt1.setDebounce(50);        // настройка антидребезга (по умолчанию 80 мс)
  butt1.setTimeout(300);        // настройка таймаута на удержание (по умолчанию 500 мс)
  butt1.setClickTimeout(600);   // настройка таймаута между кликами (по умолчанию 300 мс)
  // HIGH_PULL - кнопка подключена к GND, пин подтянут к VCC (PIN --- КНОПКА --- GND)
  // LOW_PULL  - кнопка подключена к VCC, пин подтянут к GND
  butt1.setType(HIGH_PULL);
  // NORM_OPEN - нормально-разомкнутая кнопка
  // NORM_CLOSE - нормально-замкнутая кнопка
  butt1.setDirection(NORM_OPEN);

  //debug
    Serial.begin(9600);

}

void loop() {
      butt1.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
  if (butt1.isClick()){
    Serial.println(mode);         // проверка на один клик
    switch(mode){
    case 0:
    display.clearDisplay();
 display.setCursor(1,1);
 display.setTextSize(1,2);
    display.println("1. Hall mode:");  
    display.display();
    break;

    case 1: 
    display.clearDisplay();
 display.setCursor(1,1);
 display.setTextSize(1,2);
    display.println("2. Throttle mode:");  
    display.display();
    break;

}
    mode++;
    if(mode>1){
      mode =0;
    }
    
  } 
  if (butt1.isHolded()) Serial.println("Holded");       // проверка на удержание


}
