boolean currentButton = LOW;
boolean lastButton = LOW;
int count = 0;

void setup() {
  pinMode(7, INPUT);
  pinMode(11, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  count = 0;
  while(count < 3)
  {
    Serial.print(count);
    currentButton = debounce(lastButton);

    if(lastButton == LOW && currentButton == HIGH)
    {
      count++;
      blinkNum(count);
    }
    lastButton = currentButton;
  }
  digitalWrite(11, LOW);
}

int blinkNum(int count){
  if (count == 1)
  {
    analogWrite(11, 255);
    delay(500);
    analogWrite(11, 0);
  }
  if (count == 2)
  {
    analogWrite(11, 255);
    delay(500);
    analogWrite(11, 0);
    delay(500);
    analogWrite(11, 255);
    delay(500);
    analogWrite(11, 0);
  }
  if (count == 3)
  {
    analogWrite(11, 255);
    delay(500);
    analogWrite(11, 0);
    delay(500);
    analogWrite(11, 255);
    delay(500);
    analogWrite(11, 0);
    delay(500);
    analogWrite(11, 255);
    delay(500);
    analogWrite(11, 0);
  }
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(7);
  if (last != current)
  {
    delay(5);
    current = digitalRead(7);
  }
  Serial.print(current);
  return current;
}
