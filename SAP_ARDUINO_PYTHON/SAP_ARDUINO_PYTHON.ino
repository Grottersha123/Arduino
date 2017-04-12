String TOKEN = "115666ccda8e12ffcd176f9a2c14b72";
String NAME_ACCOUNT = "1942369040trial";
String MESSAGE = "289ffc0c7adba1446c17";
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <Process.h>
//третий корпус
float N1 = 55.826090;
float E1 = 37.387760;

float N2 = 55.825867;
float E2 = 37.389916;

//amount points - колличество точек
void makeCoords(float N1, float E1,float N2, float E2, int amountPoints)
{
  float N=N1; float E=E1;
  //тут отправляем N и E в БД
  PYTHON_SEND(N,E);
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
   PYTHON_SEND(N,E);
  }
}



SoftwareSerial gpsSerial(8, 7); // create gps sensor connection
TinyGPS gps; // create gps object

void setup() {
  Bridge.begin();
  Serial.begin(9600); // connect serial
  gpsSerial.begin(9600); // connect gps sensor

  makeCoords(N1, E1, N2, E2, 10);
  
}
float lat, lon;
unsigned long fix_age;
void loop() {

  //GET_GPS();



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

    //SEND_DATA(lat, lon);

  }


}
void PYTHON_SEND(float lan, float lon)
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





void SEND_DATA(float Lot, float Lat)
{
  Process p;

  String str1;
  char tmp1[10];
  char tmp2[10];
  dtostrf(Lot, 1, 6, tmp1);
  String strLab1 = "";
  String strOut1 = strLab1 + tmp1;
  //
  dtostrf(Lat, 1, 6, tmp2);
  String strLab = "";
  String strOut = strLab + tmp2;

  str1 = "{\"mode\":\"async\",\"messageType\":\"" + MESSAGE + "\",\"messages\":[{\"timestamp\":" + String(0) + ",\"Latitude\":" + String(strOut1) + ",\"Longitude\":" + String(strOut) + "}]}";

  //char cmd[] = "curl -i -k -f -H Authorization: Bearer "+ TOKEN + " -H Content-Type: application/json;charset=UTF-8 -X POST https://iotmmsp" + NAME_ACCOUNT + ".hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/9d791d17-f73f-47d7-941b-69ea6c670939 -d";
  //char cmd1[] = "curl -i -k -f -H Authorization: Bearer " + TOKEN + " -H Content-Type: application/json;charset=UTF-8 -X POST https://iotmmsp" + NAME_ACCOUNT + ".hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/";
  char hellostr[] =  "<html><head><title>hello world</title></head>";

 // Serial.println(cmd.length());
 // Serial.println(cmd1.length());
 // p.runShellCommand(cmd + str1);
 // Serial.println(cmd1);
  // Serial.println(p.exitValue());

  //p.close();

}

void pushToCloud1(float Lot, float Lat)
{
  // curl --header 'Authorization: Bearer 5adce4964138342473a663b2d22e8' --header 'Content-Type:application/json;charset=UTF-8' -k -X POST https://iotmmsp1941889917trial.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/d70fbdef-dba4-4f59-85eb-9e8131582b3c --data '{"mode":"async","messageType":"091b562d43f936bef85b","messages":[{"Temperature":23, "Light":210, "Humidity":65, "ID":1}]}'
  Process p;
  p.begin("curl");

  p.addParameter("-k");
  p.addParameter("-f");
  // p.addParameter("-i");
  // p.addParameter("-v");
  p.addParameter("-H");
  p.addParameter("Authorization: Bearer " + TOKEN);
  p.addParameter("-H");
  p.addParameter("Content-Type: application/json;charset=UTF-8");
  p.addParameter("-X");
  p.addParameter("POST");
  //p.addParameter("https://iotmmsp1942369040trial.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/c2721cd2-3e96-4858-9cb6-7fb5d0c7a29e");//TLH
  //p.addParameter("https://iotmmsp" + NAME_ACCOUNT + ".hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/9d791d17-f73f-47d7-941b-69ea6c670939"); //geo
  p.addParameter("http://requestb.in/1ahfbrj1"); //geo
  p.addParameter("--data");
  String str1;
  char tmp1[10];
  char tmp2[10];
  dtostrf(Lot, 1, 6, tmp1);
  String strLab1 = "";
  String strOut1 = strLab1 + tmp1;
  //
  dtostrf(Lat, 1, 6, tmp2);
  String strLab = "";
  String strOut = strLab + tmp2;

  str1 = "{\"mode\":\"async\",\"messageType\":\"" + MESSAGE + "\",\"messages\":[{\"timestamp\":" + String(0) + ",\"Latitude\":" + String(strOut1) + ",\"Longitude\":" + String(strOut) + "}]}";
  p.addParameter(str1);
  p.run();
  /*while (p.available() > 0) {
    char c = p.read();
    Serial.print(c);
  }*/
  Serial.println(str1);
  Serial.print("Exit: ");

  Serial.println(p.exitValue());
  p.close();
  //Serial.println(p.read());
}




