int v_out = 13;//define a PWM pin number
int val = 255;//an integer value used for PWM(can vary between0 and 255)
int tim = 2000; //time in ms

void setup()
  {pinMode(v_out, OUTPUT); //define pin 11as OUTPUT
  }
void loop()
{

    //send a PWM signal to pin 9 with a duty cycle of 140/255 
  analogWrite(v_out, val);
  delay(tim/2);
  analogWrite(v_out, 0);
  delay(tim/2);

}
