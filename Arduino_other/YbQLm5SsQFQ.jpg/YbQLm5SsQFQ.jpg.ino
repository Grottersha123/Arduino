void setup()
{
  Serial.begin(9600);
  Serial.println("Hello Mike");
  pinMode(7,INPUT_PULLUP);
  pinMode(8,OUTPUT);
  
}
boolean buttonWasUp = true;
boolean enabledLed = false;
int i = 0;

void loop()
{ //int ter = delay(10);
  boolean buttonIsUp = digitalRead(7);
  if (buttonWasUp && !buttonIsUp){
    delay(10);
    buttonIsUp = digitalRead(7);
    if (!buttonIsUp){
      i++;
     if (i == 3  ){
       i=0;
       enabledLed = !enabledLed;
      digitalWrite(8,enabledLed);
     }
     else if (i==2){
     toggle(8,20);
     }
    }
  }
  buttonWasUp = buttonIsUp;
  
}

void toggle(int pin, int del)
{
 digitalWrite(pin,HIGH);
 delay(del);
 digitalWrite(pin,LOW);   
 delay(del);
}
