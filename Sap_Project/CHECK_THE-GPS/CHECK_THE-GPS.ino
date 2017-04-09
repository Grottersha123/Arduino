#include <SoftwareSerial.h>
//начало вставки кода №1

//#include <LiquidCrystal_I2C.h>
//конец вставки кода №1
#include <TinyGPS.h>
#include <Process.h>
/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

TinyGPS gps;
SoftwareSerial ss(8, 7);
int led = 6;
static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void print_str(const char *str, int len);
//начало вставки кода №2
//LiquidCrystal_I2C lcd(0x27, 20, 4);
//конец вставки кода №2
void setup()
{
  Bridge.begin();
  Serial.begin(9600);
  
 pinMode(led, OUTPUT);


  ss.begin(9600);
  

  //начало вставки кода №3
  // lcd.begin();
  //lcd.backlight();
  //конец вставки кода №3
  
}

void loop()
{
  float flat, flon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;


  //начало вставки кода №4
  //      lcd.clear();
  //lcd.print(gps.f_altitude());
  gps.f_get_position(&flat, &flon, &age);
 
  if (flat < 1000 && flat != 0) {
    Serial.print(" N ");
    Serial.print(flat, 6);
    Serial.print(" E ");
    Serial.print(flon, 6);
    digitalWrite(6, HIGH);
}
Serial.print(" N ");
Serial.print(flat, 6);
Serial.print(" E ");
Serial.print(flon, 6);
//начало вставки кода №4
 pushToCloud1(flat,flon);
Serial.println();




smartdelay(1000);
}
void pushToCloud1(float Lot, float Lat)
{
  //Передача данных в HCP с помощью встроенной в Linux служебной программы curl
  // Строка для проверки передачи данных в HCP с Arduino в терминальном режиме
  // Использовать через Putty
  // Login: root
  // Password: 12345678
  //Distance();
  // curl --header 'Authorization: Bearer 5adce4964138342473a663b2d22e8' --header 'Content-Type:application/json;charset=UTF-8' -k -X POST https://iotmmsp1941889917trial.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/d70fbdef-dba4-4f59-85eb-9e8131582b3c --data '{"mode":"async","messageType":"091b562d43f936bef85b","messages":[{"Temperature":23, "Light":210, "Humidity":65, "ID":1}]}'
  Process p;
  p.begin("curl");
  p.addParameter("-k");
  p.addParameter("-f");
  p.addParameter("-H");
  p.addParameter("Authorization: Bearer 115666ccda8e12ffcd176f9a2c14b72");
  p.addParameter("-H");
  p.addParameter("Content-Type: application/json;charset=UTF-8");
  //p.addParameter("-X");
  p.addParameter("POST");
  //p.addParameter("https://iotmmsp1942369040trial.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/c2721cd2-3e96-4858-9cb6-7fb5d0c7a29e");//TLH
  p.addParameter("https://iotmmsp1942369040trial.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/9d791d17-f73f-47d7-941b-69ea6c670939"); //geo
  p.addParameter("--data");
  String str1;
//  str = "{\"mode\":\"async\",\"messageType\":\"d59799c5a37c7a186f97\",\"messages\":[{\"Temperature\":" + String(Temperature_value) + ",\"Light\":" + String(Light_value) + ",\"Humidity\":" + String(Humidity_value) + ",\"ID\":" + String(ID_value) + "}]}";
  str1 = "{\"mode\":\"async\",\"messageType\":\"289ffc0c7adba1446c17\",\"messages\":[{\"timestamp\":" + String(0) + ",\"Latitude\":" + String(Lot) + ",\"Longitude\":" + String(Lat) + "}]}";
  p.addParameter(str1);
  p.run();
  
  //Вывод результата работы утилиты curl в серийный порт
  Serial.println(str1);
  Serial.print("Exit: ");
  Serial.println(p.exitValue());
  //Serial.println(lon);
  //Serial.println(lat);
  //Serial.print(lon);
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

static void print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i = flen; i < len; ++i)
      Serial.print(' ');
  }
  smartdelay(0);
}

static void print_int(unsigned long val, unsigned long invalid, int len)
{
  char sz[32];
  if (val == invalid)
    strcpy(sz, "*******");
  else
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i = strlen(sz); i < len; ++i)
    sz[i] = ' ';
  if (len > 0)
    sz[len - 1] = ' ';
  Serial.print(sz);
  smartdelay(0);
}

static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("********** ******** ");
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
            month, day, year, hour, minute, second);
    Serial.print(sz);
  }
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
  smartdelay(0);
}

static void print_str(const char *str, int len)
{
  int slen = strlen(str);
  for (int i = 0; i < len; ++i)
    Serial.print(i < slen ? str[i] : ' ');
  smartdelay(0);
}
