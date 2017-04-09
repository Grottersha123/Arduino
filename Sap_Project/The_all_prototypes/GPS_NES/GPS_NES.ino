#include <SoftwareSerial.h>

SoftwareSerial GSMport(4,3); 
        
void setup(){
  Serial.begin(9600);
  GSMport.begin(9600); 
  GSMport.println( "AT + CGPSPWR = 1"); 
  GSMport.println( "AT+CGPSINF = 4");
 

 
}
unsigned char buffer[64]; // buffer
int count=0;
String response = ""; 
void loop(){
  char c;
  String str;
 // Serial.println("LOL");
   
  while (GSMport.available()) {  
      //отправляем данные с GSM в Serial     
      buffer[count++]=GSMport.read();
      if(count == 64)
            break;
     // c = GSMport.read();
      // str += char(GSMport.read());
      Serial.write(buffer,count);
      //Serial.print(str);   
    clrBuff();
     count = 0;   
  }
  //Serial.println(str);
  }
void clrBuff()
{
    for (int i=0; i<count;i++)
    {
        buffer[i]=NULL;
    }
}
