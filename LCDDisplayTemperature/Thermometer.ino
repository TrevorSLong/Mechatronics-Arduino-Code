//MECH307 HW4, Group 12, Code by Trevor Long
//Inialize variables
boolean currentButton = LOW;
boolean lastButton = LOW;
int count = 1;
int ButtonPin = 2;
int Buttonread = 0;
int tempPin = 0;
int ThermistorPin = A0;

//Setup for LCD
#include <LiquidCrystal.h>
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup()
{
  lcd.begin(16, 2);
  pinMode(ThermistorPin, INPUT); //Thermistor pin input
  pinMode(ButtonPin, INPUT); //Button pin input
}

void loop()
{
  
while(count < 2) { //Debounce code that changes "count" if button is pressed
  
 
    currentButton = debounce(lastButton);

    if(lastButton == LOW && currentButton == HIGH)
    {
      //Code below toggles between count = 1 and count = 2
      if (count == 0) {
        count = 1;
      }
      else {
        count = 0;
      }
      //End toggle code
    }
    lastButton = currentButton;
    break; //breaks out of debounce so temperature can be displayed
}

while (count == 0) //If count = 0 display temp in Celcius
{
    int tempReading = analogRead(tempPin);
    double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
    float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
    float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
    
    // Display Temperature in C
    lcd.setCursor(0, 0);
    lcd.print("Temp:         C  ");
    lcd.setCursor(6, 0);
    lcd.print(tempC);
    delay(200);
    break; //breaks loop so that button signal can be read
}
while (count == 1) //If count = 1 display temp in Fahrenheit
{
    int tempReading = analogRead(tempPin);
    double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
    float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
    float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
    
    // Display Temperature in F
    lcd.setCursor(0, 0);
    lcd.print("Temp:         F  ");
    lcd.setCursor(6, 0);
    lcd.print(tempF);
    delay(200);
    break; //breaks loop so that button signal can be read

}
}

boolean debounce(boolean last) //Debounce function
{
  boolean current = digitalRead(ButtonPin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(ButtonPin);
  }
  return current;
}
