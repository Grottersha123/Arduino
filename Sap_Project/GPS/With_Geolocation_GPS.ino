#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <TroykaDHT11.h>



//#include <Ultrasonic.h>

#include <Process.h>


// Инициализация переменных
DHT11 dht(11);

int check;
int Light_v;
int Temp_v;
float lat = 0.0;
float lon = 0.0;
int Humidity_v;
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
int ID_v;
const int trigPin = 2;
const int echoPin = 1;

// defines variables
long duration;
double distance;
String jason;
//Ultrasonic ultrasonic(1,2);
TinyGPS gps;
SoftwareSerial ss(4, 3);

void setup() {

  Bridge.begin();
  Serial.begin(9600);
  //  Distance();
  //  dht.begin();
  ID_v = 0;
  //runCurl();
  // Bridge.begin();

}
void loop() {
  // Считываем данные с цифрового датчика температуры и влажности
  check = dht.read();

  //Считываем уровень света

  Light_v = analogRead(A0);
  Serial.print("Light = ");
  Serial.println(Light_v);
  //Считываем уровень температуры
  Temp_v = dht.getTemperatureC();
  Serial.print("Temperature = ");
  Serial.print(Temp_v);
  Serial.println("C \t");
  //Считываем уровень влажности
  Humidity_v = dht.getHumidity();
  Serial.print("Humidity = ");
  Serial.print(Humidity_v);
  Serial.println("%");
  Serial.println("");
  ID_v = ID_v + 1;
  float flat, flon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;
  double first = 54.922011;
  double second = 34.999696;
  // начальнные данные для коэфичента
  double third  = 54.925957;
  double fourth = 35.004588;
  del1 = (third - first) / n;
  del2 = (fourth - second) / n;
  a_1 = del1 / (flat - LAT_1);
  a_2 = del1 / (flon - LON_1);
  LAT_1 += a_1 * (flat - LAT_1);
  LON_1 += a_2 * (flon - LON_1);
  gps.f_get_position(&flat, &flon, &age);
  //char* LAT;
  //dtostrf(flat, 10, 7, LAT);
  Serial.println(LAT_1);
  Serial.println(LON_1, 12);
 

  //Передача данных в HCP
  // get distance
  //Distance();
  // runCurl();
   pushToCloud1(LAT_1,LON_1);
  //delay(5000);
  // pushToCloud(Temp_v, Light_v, Humidity_v, ID_v);



  // Distance();
  delay(1000);

}


float Take_Location1(String jason)
{
  int val = jason.indexOf("lat") + 5;
  String OH;
  while (jason[val] != ',')
  {
    OH += jason[val];
    val++;
  }
  float Loc = OH.toFloat();
  return Loc;
}

float Take_Location(String jason)
{
  int val = jason.indexOf("lon") + 5;
  String OH;
  while (jason[val] != ',')
  {
    OH += jason[val];
    val++;
  }
  float Loc = OH.toFloat();
  return Loc;
}
void runCurl() {
  // запускаем команду "curl" и возвращаем Arduino ascii-лого из сети
  // curl - это консольная утилита для передачи данных через различные Интернет-протоколы
  Process p;        // Создаем процесс и называем его "p"
  p.begin("curl");  // Процесс, который будет вызывать команду "curl"
  p.addParameter("http://ip-api.com/json"); // Добавляем к "curl" URL страницы
  p.run();      // Запускаем процесс и ожидаем его завершения

  // Выводим логотип Ардуино через последовательный порт
  // выходные данные процесса можно считать с помощью потоков
  while (p.available() > 0) {
    char c = p.read();
    // Serial.print(c);
    jason += c;
  }
  //jason = "LOL";
  //Serial.println(jason);
  Serial.println("NEXT");
  Serial.println(Take_Location(jason));
  // Distance();
  lon = Take_Location1(jason);
  lat = Take_Location(jason);




  Serial.flush();
}



void pushToCloud1(double Lot, double Lat)
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
  char tmp1[10];
  char tmp2[10];
  dtostrf(Lot,1,6,tmp1);
  String strLab1 = "";
  String strOut1 = strLab1 + tmp1;
  //
  dtostrf(Lat,1,6,tmp2);
  String strLab = "";
  String strOut = strLab + tmp2;
 // dtostrf(LAT_1,1,6,LAT);
 // dtostrf(LAT_1,1,6,LAT);
  str1 = "{\"mode\":\"async\",\"messageType\":\"289ffc0c7adba1446c17\",\"messages\":[{\"timestamp\":" + String(0) + ",\"Latitude\":" + strOut1 + ",\"Longitude\":" + strOut + "}]}";
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











void pushToCloud_Model(float Lot, float Lat)
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


















void pushToCloud(int Temperature_value, int Light_value, int Humidity_value, int ID_value)
{
  //Передача данных в HCP с помощью встроенной в Linux служебной программы curl
  // Строка для проверки передачи данных в HCP с Arduino в терминальном режиме
  // Использовать через Putty
  // Login: root
  // Password: 12345678
  // curl —header 'Authorization: Bearer 5adce4964138342473a663b2d22e8' —header 'Content-Type:application/json;charset=UTF-8' -k -X POST https://iotmmsp1941889917trial.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/d70fbdef-dba4-4f59-85eb-9e8131582b3c —data '{"mode":"async","messageType":"091b562d43f936bef85b","messages":[{"Temperature":23, "Light":210, "Humidity":65, "ID":1}]}'
  Process p;
  p.begin("curl");
  p.addParameter("-k");
  p.addParameter("-f");
  p.addParameter("-H");
  p.addParameter("Authorization: Bearer 5adce4964138342473a663b2d22e8");
  p.addParameter("-H");
  p.addParameter("Content-Type: application/json;charset=UTF-8");
  //p.addParameter("-X");
  p.addParameter("POST");
  p.addParameter("https://iotmmsp1942369040trial.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/c2721cd2-3e96-4858-9cb6-7fb5d0c7a29e");
  p.addParameter("--data");
  String str;
  str = "{\"mode\":\"async\",\"messageType\":\"d59799c5a37c7a186f97\",\"messages\":[{\"Temperature\":" + String(Temperature_value) + ",\"Light\":" + String(Light_value) + ",\"Humidity\":" + String(Humidity_value) + ",\"ID\":" + String(ID_value) + "}]}";
  p.addParameter(str);
  p.run();
  //Вывод результата работы утилиты curl в серийный порт
  Serial.println(str);
  Serial.println(lon);
  Serial.println(lat);
  Serial.print("Exit: ");
  Serial.println(p.exitValue());
}

