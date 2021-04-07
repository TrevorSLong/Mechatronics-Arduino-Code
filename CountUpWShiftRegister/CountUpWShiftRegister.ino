#define DATA 2      // connect to pin 14 on the 74HC595
#define LATCH 3     // connect to pin 12 on the 74HC595
#define CLOCK 4    // connect to pin 11 on the 74HC595
int data[] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 156, 122, 158, 142};
void setup() {
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
}
void loop() {
  int i;
  for ( i = 0 ; i < 10 ; i++ ) {
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, data [i]);
    digitalWrite(LATCH, HIGH);
    delay(1000);
  }
}
