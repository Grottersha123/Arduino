int val;
int ledRed = 3;
int ledGrean = 6;

void setup()
{
  
}

void loop()
{
  for (val = 0; val < 255; val++){
    analogWrite(ledGrean,val);
    analogWrite(ledRed,255-val);
    delay(5);
  }
  delay(1000);
  for (val = 255; val !=0; val--){
    analogWrite(ledGrean, val);
    analogWrite(ledRed,255-val);
    delay(5);
  }
  delay(1000);
}
