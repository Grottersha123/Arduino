void setup()
{
  pinMode(4,OUTPUT);
}
void beep(int ton, int time)
{
  tone(4, ton, time);
  delay(time + 20);
}
void loop()
{
  //первый такт
  beep(392,1000);
  beep(392,1000);
  beep(392,1000);
  beep(311,700);
  beep(466,250);
  //второй такт
  beep(392,1000);
  beep(311,700);
  beep(466,250);
  beep(392,1000);
  beep(0,1000);
  //третий такт
  beep(587,1000);
  beep(587,1000);
  beep(587,1000);
  beep(622,700);
  beep(466,250);
  //четвертый такт
  beep(370,1000);
  beep(311,700);
  beep(466,250);
  beep(392,2000);
  //2-ая строчка
  //пятый такт
  beep(784,1000);
  beep(392,700);
  beep(392,250);
  beep(784,1000);
  beep(730,700);
  beep(698,250);
  //шестой такт
  beep(659,250);
  beep(622,250);
  beep(659,500);
  beep(0,500);
  beep(415,500);
  beep(554,1000);
  beep(523,700);
  beep(493,250);
  //седьмой такт
  beep(466,250);
  beep(440,250);
  beep(466,500);
  beep(0,500);
  beep(311,500);
  beep(370,1000);
  beep(311,700);
  beep(370,250);
  //восьмой такт
  beep(466,1000);
  beep(392,700);
  beep(466,250);
  beep(587,2000);
  //3-я строчка
  // 9 такт
  beep(784,1000);
  beep(392,700);
  beep(392,250);
  beep(784,1000);
  beep(730,700);
  beep(698,250);
  //10 такт
  beep(659,250);
  beep(622,250);
  beep(659,500);
  beep(0,500);
  beep(415,500);
  beep(554,1000);
  beep(523,700);
  beep(493,250);
  //11 такт
  beep(466,250);
  beep(440,250);
  beep(466,500);
  beep(0,500);
  beep(311,500);
  beep(370,1000);
  beep(311,700);
  beep(466,250);
  //12 такт
  beep(392,1000);
  beep(311,700);
  beep(466,250);
  beep(392,2000);
}
