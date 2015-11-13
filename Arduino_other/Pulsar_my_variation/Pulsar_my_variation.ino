#define FIRST 2
#define LAST 11

void setup()
{
  for (int i = FIRST; i < LAST; i++){
    pinMode(i,OUTPUT);
  }
}

void loop()
{
  for( int i = FIRST; i <= LAST; i++){ 
    TurnON(i);
  }
  for (int i = LAST; i != FIRST; i--){
    TurnON(i);
    //TurnON(10);
  }
}



void TurnON(int pin)
{
  digitalWrite(pin,HIGH);
  delay(100);
  digitalWrite(pin,LOW);
}
