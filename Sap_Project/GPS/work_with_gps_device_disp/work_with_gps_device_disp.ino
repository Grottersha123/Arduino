#include <SoftwareSerial.h>
//начало вставки кода №1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//конец вставки кода №1
#include <TinyGPS.h>

#include <Process.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

int i = 0;
int n = 100;
long double a_1;
long double a_2;
//

//
double LAT_1 = 54.922011;
double LON_1 = 34.999696;
//начальные данные

// высчитывание дельты
long double del1;
long double del2;
TinyGPS gps;
SoftwareSerial ss(4, 3);

static void smartdelay(unsigned long ms);
//начало вставки кода №2
LiquidCrystal_I2C lcd(0x27, 20, 4);
//конец вставки кода №2
void setup()
{
  Bridge.begin();
  Serial.begin(9600);

  // Serial.print("Testing TinyGPS library v. "); Serial.println(TinyGPS::library_version());


  ss.begin(9600);

  //начало вставки кода №3

  //конец вставки кода №3
}
void loop()
{
  float flat, flon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;
  double first = 54.922011;
  double second = 34.999696;
  // начальнные данные для коэфичента
  double third  = 54.925957;
  double fourth = 35.004588;
  del1 = (third-first)/n;
  del2 = (fourth - second)/n;
  a_1 = del1/(flat - LAT_1);
  a_2 = del1/(flon - LON_1);
  LAT_1+= a_1*(flat-LAT_1);
   LON_1+= a_2 * (flon-LON_1);
  Serial.println();
  // print_int(gps.satellites(), TinyGPS::GPS_INVALID_SATELLITES, 5);
  // print_int(gps.hdop(), TinyGPS::GPS_INVALID_HDOP, 5);
  gps.f_get_position(&flat, &flon, &age);
  char tmp[10];
  dtostrf(LAT_1,1,6,tmp);
  String strLab = "";
  String strOut = strLab + tmp;
 // dtostrf(LAT_1,1,6,LAT);
  Serial.println(strOut);
  Serial.println(LON_1, 12);
  
  i++;
  Serial.println(i);
//  Serial.print(del2);

  /*if (flat <= 1000.0)
    {
    double a_1 = del1 / abs(flat - LAT_1);
    double a_2 = del2 / abs(flon - LON_1);
    LAT_1+= a_1*abs(flat-LAT_1);
    LON_1+= a_2 * abs(flon-LON_1);

    Serial.println("Start new coordinates");
    Serial.println(LAT_1,6);
    Serial.println(LON_1,6);
    }*/






  smartdelay(1000);
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}





