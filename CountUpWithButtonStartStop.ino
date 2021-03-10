#define DATA 2      // connect to pin 14 on the 74HC595
#define LATCH 3     // connect to pin 12 on the 74HC595
#define CLOCK 4    // connect to pin 11 on the 74HC595
boolean currentButton = LOW;
boolean lastButton = LOW;
int count = 0;
int i = 0;

int data[] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 156, 122, 158, 142};
void setup() {
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(7, INPUT);
  
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, 252);
  digitalWrite(LATCH, HIGH);
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(7);
  if (last != current)
  {
    delay(5);
    current = digitalRead(7);
  }
  return current;
}

int disNumber(int count){
  if (count == 1){
      while ( i < 10 ) {
        digitalWrite(LATCH, LOW);
        shiftOut(DATA, CLOCK, LSBFIRST, data [i]);
        digitalWrite(LATCH, HIGH);
        delay(1000);
        i++;
      } 
  }
  if (count == 2){
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, 252);
    digitalWrite(LATCH, HIGH);
    count = 0;
    i = 0;
  }
  return i;
}

void loop() {
  count = 0;
  while (count < 2){
    currentButton = debounce(lastButton);

    if(lastButton == LOW && currentButton == HIGH)
    {
      count++;
      disNumber(count);
    }
    lastButton = currentButton;
  }
}
