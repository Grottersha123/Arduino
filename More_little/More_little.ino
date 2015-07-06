int val;
int ledRed = 3;
int ledGrean = 6;

void setup()
{ 
}
// медленно ,загорается через 1000 милисекунд начинает медленно потухать
void loop()
{
  for (val = 0; val < 255; val++){ 
    analogWrite(ledGrean,val);
    analogWrite(ledRed,255-val); // изменяется значение от 255 до 0
    delay(5);
  }
  delay(1000);
  for (val = 255; val !=0; val--){
    analogWrite(ledGrean, val);
    analogWrite(ledRed,255-val); от 0 до 255 
    delay(5);
  }
  delay(1000);
}
