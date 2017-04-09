#include <SoftwareSerial.h>

/* Connect device Rx - 10, Tx - 11 */
#define rxGPS 8
#define txGPS 7
SoftwareSerial serialGPS = SoftwareSerial(rxGPS, txGPS);
String stringGPS = "";

void setup() {

Serial.begin(9600);
  serialGPS.begin(4800);
  while(!Serial);
  Serial.println("Started");

  // GPS Setup

  digitalWrite(txGPS,HIGH);

  // Cut first gibberish
  while(serialGPS.available())
    if (serialGPS.read() == '\r')
      break;
}

void loop()
{
  bool s = checkGPS();
  if(s == true)
  {
    Serial.println(s);
  }
}

// Check GPS and returns string if full line recorded, else false
bool checkGPS()
{
  if (serialGPS.available())
  {
    char c = serialGPS.read();
    if (c != '\n' && c != '\r')
    {
      stringGPS  = c;
    }
    else
    {
      if (stringGPS != "")
      {
        String tmp = stringGPS;
        stringGPS = "";
        return tmp;
      }
    }
  }
  return false;
}
