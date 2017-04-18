String TOKEN = "115666ccda8e12ffcd176f9a2c14b72";
String NAME_ACCOUNT = "1942369040trial";
String MESSAGE = "289ffc0c7adba1446c17";
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <Process.h>
#include <TroykaDHT11.h>
//третий корпус
float N1 = 55.826090;
float E1 = 37.387760;

float N2 = 55.825867;
float E2 = 37.389916;
DHT11 dht(11);

int check;
int Light_v;
int Temp_v;
float lat = 0.0;
float lon = 0.0;
int Humidity_v;
int ID_v;
//amount points - колличество точек
void makeCoords(float N1, float E1,float N2, float E2, int amountPoints)
{
  float N=N1; float E=E1;
  //тут отправляем N и E в БД
  //PYTHON_SEND(N,E);
   Serial.print(N,6);
   Serial.print(" ");
   Serial.println(E,6);

  
  float deltaN = N2 - N1;
  float deltaE = E2 - E1;
  deltaN/=amountPoints;
  deltaE/=amountPoints;
  for(int i =0;i<amountPoints;i++)
  {
   N+=deltaN;
   E+=deltaN;
   Serial.print(N,6);
   Serial.print(" ");
   Serial.println(E,6);
   //тут отправляем N и E в БД
   //PYTHON_SEND(N,E);
  }
}



SoftwareSerial gpsSerial(8, 7); // create gps sensor connection
TinyGPS gps; // create gps object

void setup() {
  Bridge.begin();
  Serial.begin(9600); // connect serial
  dht.begin();
  ID_v = 0;
  gpsSerial.begin(9600); // connect gps sensor

 // makeCoords(N1, E1, N2, E2, 10);
  
}

unsigned long fix_age;
void loop() {

  GET_GPS();
  GET_SENSORS();
  //PYTHON_SEND_TWO_TABLE(100,100,1,23,34,45);
  


}
// берет данные с модуля и перекодирует в нужный формат
void GET_SENSORS()
{
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
}
void GET_GPS()
{ 
  while (gpsSerial.available()) { // check for gps data
    if (gps.encode(gpsSerial.read())) { // encode gps data
      //lol+= char(gpsSerial.read());
      //Serial.write(char(gpsSerial.read()));
    gps.f_get_position(&lat, &lon, &fix_age);
     Serial.print("lat: "); Serial.print(lat, 6); Serial.print(" "); // print latitude

     Serial.print("lon: "); Serial.println(lon, 6); // print longitude*/
      // Create a process and call it "p"
     // pushToCloud1(lat, lon);
    }

    PYTHON_SEND_GEO(lat,lon);

  }


}
void PYTHON_SEND_GEO(float lan, float lon)
{
  String cmd;
  Process p; // Create a process and call it "p"
  
  p.begin("python"); // Process that launch the "python" command
  String str1;
  char tmp1[10];
  char tmp2[10];
  dtostrf(lan, 1, 6, tmp1);
  String strLab1 = "";
  String strOut1 = strLab1 + tmp1;
  //
  dtostrf(lon, 1, 6, tmp2);
  String strLab = "";
  String strOut = strLab + tmp2;
  cmd = "python /mnt/sda1/arduino/r.py "+String(strOut1) + " " + String(strOut);
  p.runShellCommand(cmd);
  Serial.print("Exit: ");
  Serial.println(p.exitValue());
  p.close();
}



void PYTHON_SEND_SENSOR(int id,float hum,float light, float temp)
{
  String cmd;
  Process p; // Create a process and call it "p"
  
  p.begin("python"); // Process that launch the "python" command
 
  //

  cmd = "python /mnt/sda1/arduino/r_1.py "+ String(id)+ " " + String(hum)+ " " + String(light)+ " " + String(temp);
  p.runShellCommand(cmd);
  Serial.print("Exit: ");
  Serial.println(p.exitValue());
  p.close();
}


void PYTHON_SEND_TWO_TABLE(float lan, float lon,int id,float hum,float light, float temp)
{
  String cmd;
  Process p; // Create a process and call it "p"
  
  p.begin("python"); // Process that launch the "python" command
  String str1;
  char tmp1[10];
  char tmp2[10];
  dtostrf(lan, 1, 6, tmp1);
  String strLab1 = "";
  String strOut1 = strLab1 + tmp1;
  //
  dtostrf(lon, 1, 6, tmp2);
  String strLab = "";
  String strOut = strLab + tmp2;
  cmd = "python /mnt/sda1/arduino/r.py "+String(strOut1) + " " + String(strOut) + " " + String(id)+ " " + String(hum)+ " " + String(light)+ " " + String(temp);
  p.runShellCommand(cmd);
  Serial.print("Exit: ");
  Serial.println(p.exitValue());
  p.close();
}









