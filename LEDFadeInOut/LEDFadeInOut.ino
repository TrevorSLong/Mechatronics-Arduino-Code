int v_out = 11;//define a PWM pin number
int val = 0;//an integer value used for PWM(can vary between0 and 255)
int val2 = 0; //val2 for brightness down
int tim = 500; //time in ms

void setup()
  {pinMode(v_out, OUTPUT); //define pin 11as OUTPUT
  }
void loop()
{

while (val < 250)
{
   //send a PWM signal to pin 9 with a duty cycle of 140/255 
  analogWrite(v_out, val);
  delay(tim/2);
  val = val+1;
}
 val2 = 250;

while (val2 > 0)
{
   //send a PWM signal to pin 9 with a duty cycle of 140/255 
  analogWrite(v_out, val2);
  delay(tim/2);
  val2 = val2-1;
}

 val = 0;
}
