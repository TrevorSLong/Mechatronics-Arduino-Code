// Include the libraries:
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include "RTClib.h"

//DHT initialization
#define DHTPIN 2 // Set DHT pin
#define DHTTYPE DHT11   // set DHT type 11 
DHT dht = DHT(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino:
int DHTResult = 0;
float h = 0;
float hif = 0;

//PIR initialization
#define pirPin 7 //SET PIR Sensor pin
int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 5000;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;
int PIRResult = 0;
bool motion = 0;
bool motionLast = 0;
int motioncount = 0;
bool absent = 0;

//LCD initialization
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
int lcdBacklightPin = A0;

//cyclic initialization
int tempTimer = 0;

//initialize rtc
RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int hour = 0;
int tod = 1;

void setup() {
  Serial.begin(9600); // Begin serial communication at a baud rate of 9600:

  dht.begin(); // Setup DHT sensor

  rtc.begin(); //initialize rtc
  rtc.start();

  lcd.begin(16, 2); //set the type of LCD display
  lcd.print("Please wait.."); //put please wait on the screen while we  wait for the first temp input
  pinMode(lcdBacklightPin, OUTPUT);

  pinMode(pirPin, INPUT); //define the PIR sensor pin as input
}

void loop() {
  delay(200); //makes this routine run at 50ms
  DateTime now = rtc.now();
  tempTimer = tempTimer + 1;
  if (tempTimer == 25){
    h = getHumidity();
    hif = getHeatIndex();
  }

  motion = PIRSensor();

  if(motion == 0 and motionLast == motion){
    motioncount = motioncount + 1;
  }
  else if(motion == 1 and motionLast == motion){
    motioncount = motioncount + 1;
  }
  else{
    motioncount = 0;
  }

  if ((motionLast != motion) && (motion == 1) && absent == 1){
    lcd.clear();
    lcd.home();
    lcd.print("Welcome Back.");
    Serial.print("Welcome Back");
    motioncount = 0;
    absent  = 0;
    tempTimer = 0;
    delay(3000);
  }
  else if ((motion == 0) && motioncount == 300){
    lcd.clear();
    lcd.home();
    lcd.print("Goodbye.");
    Serial.print("Goodbye");
    absent = 1;
    tempTimer = 0;
    delay(3000);
  }
  else if ((h != 0) && (hif != 0) && tempTimer == 50) {
    lcd.clear();
    lcd.home();
    lcd.print("Temp: ");
    lcd.print(round(hif));
    lcd.print(" \xDF");
    lcd.print("F");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(round(h));
    lcd.print("%");

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" % ");
    Serial.print("Heat index: ");
    Serial.print(hif);
    Serial.print(" \xC2\xB0");
    Serial.println("F");

    //tempTimer = 0;
  }
  else if (tempTimer == 100 || tempTimer == 108 || tempTimer == 116 || tempTimer == 124 || tempTimer == 132 || tempTimer == 140 || tempTimer == 148 || tempTimer == 156 || tempTimer == 164 || tempTimer == 172 || tempTimer == 180 || tempTimer == 188 || tempTimer == 192){
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    if (tempTimer == 100){
      lcd.clear();
    }
    lcd.home();
    lcd.setCursor(4, 0);
    //lcd.print("Time: ");
    if (now.hour() >= 13){
      hour = now.hour() - 12;
      tod = 2;
    }
    else {
      tod = 1;
    }
    if (now.hour() < 10){
      lcd.print("0");
    }
    lcd.print(hour, DEC);
    lcd.print(':');
    if (now.minute()<10){
      lcd.print("0");
    }
    lcd.print(now.minute(), DEC);
    //lcd.print(':');
    //lcd.print(now.second(), DEC);
    lcd.print(" ");
    if (tod == 1){
      lcd.print("AM");
    }
    else{
      lcd.print("PM");
    }

    lcd.setCursor(3, 1);
    if (now.month() < 10){
      lcd.print("0");
    }

    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);

    //tempTimer = 0;
  }
  else if (tempTimer == 200){
    tempTimer = 0;
  }
  motionLast = motion;
}

float getHumidity() {
  
  float h = dht.readHumidity(); // Read the humidity in %

  if (isnan(h)) { // Check if any reads failed and exit early (to try again):
    Serial.println("Failed to read from Humidity sensor!");
    return 0;
  }
  else {
    return h;
  }
}

float getHeatIndex() {
  
  float f = dht.readTemperature(true); // Read the temperature as Fahrenheit:

  if (isnan(f)) { // Check if any reads failed and exit early (to try again):
    Serial.println("Failed to read from temperature sensor!");
    return 0;
  }
  else {
    float hif = dht.computeHeatIndex(f, h); // Compute heat index in Fahrenheit (default):
    return hif;
  }
}

bool PIRSensor() {
   if(digitalRead(pirPin) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         Serial.println("Motion detected.");
         return 1;
      }
      takeLowTime = true;
   }
   else if(digitalRead(pirPin) == LOW) {
      if(takeLowTime){
         lowIn = millis();takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > pause) {
         PIRValue = 0;
         lockLow = true;
         Serial.println("Motion ended.");
         return 0;
      }
    }
  }