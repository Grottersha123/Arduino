#include <SoftwareSerial.h>
 
SoftwareSerial GSMport(3, 2); // RX, TX 
typedef struct {     
    String latitude;     
   String longitude;     
  String datetime;
} MyDataGPS;
 
MyDataGPS dataGPS;
 
void gprs_init(void);
MyDataGPS getGPSLocation(void);
void gprs_send(String dataa, String datab);
String ReadGSM(); 
 
unsigned long millisperiod=0;
 
void setup() {    
    Serial.begin(9600);   
    GSMport.begin(9600);   
   //устанавливаем чтобы номер входящего звонка определялся
   GSMport.println("AT+CLIP=1");
   delay(300);   
   GSMport.println("AT+DDET=1"); //устанавливаем прием DTMF   
   delay(300);   
   gprs_init();
} 
 
void loop() {   
   char c;   
   String str; 
   millisperiod=millis();
   // отправка данных каждые 10 сек
   if (millis()-millisperiod/10000) {   
      dataGPS = getGPSLocation();
      gprs_send(dataGPS.latitude, dataGPS.longitude);
      
   }    
   while (GSMport.available()) {  
      //отправляем данные с GSM в Serial     
      c = GSMport.read();     
      Serial.write(c);     
      delay(10);   
   }   
}  
//функция определения местоположения по GPS
MyDataGPS getGPSLocation(void) {  
   String v,v1,v2;
   String data[5];
   MyDataGPS d;
   int a = 0,b = 0;
  
   GSMport.println("AT+CGNSPWR=1");
   delay(1000);
   Serial.println(ReadGSM());
   GSMport.println("AT+CGNSINF");
   delay(400);  
   v = ReadGSM();   
   Serial.println(v);      
   for(int i=0;i<5;i++) {
      //парсинг данных между запятыми в массив строк   
      a = v.indexOf(",",a);
      //первое вхождение запятой   
      if(a!=-1) {
         b = v.indexOf(",",a+1);  //второе вхождение запятой
         data[i] = v.substring(a+1,b);     
         Serial.println(String("Data: " + String(i)+" - "+ data[i]));     
         a = b;   
      } 
   }   
   d.datetime = data[1];   
   d.latitude = data[2];   
   d.longitude = data[3];   
   return d;
} 
//Процедура начальной инициализации GSM модуля для GPRS
void gprs_init(void) {    
    int d = 500;   
   Serial.println("GPRS init start");
   delay(d * 4);   
   //Установка настроек подключения   
   GSMport.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");  
   delay(d * 5);   
   //показываем ответ от GSM модуля   
   Serial.println(ReadGSM());  
   delay(d * 5);   
   //Установка APN   
   GSMport.println("AT+SAPBR=3,1,\"APN\",\"internet.beeline.ru\"");
   delay(d);   
   Serial.println(ReadGSM());
   delay(d * 2);   
   //Устанавливаем соединение GPRS
   GSMport.println("AT+SAPBR=1,1");    
   delay(d * 2);   
   Serial.println(ReadGSM());  
   delay(d * 2);   
   //Проверяем как настроилось
   GSMport.println("AT+SAPBR=2,1");  
   delay(d);   
   Serial.println(ReadGSM());  
   delay(d * 5);    
   Serial.println("GPRS init complete");  
} 
//функция чтения данных от GSM модуля   
String ReadGSM() {  
   char c;   
   String str;   
 
   while (GSMport.available()) {  
      //сохраняем входную строку в переменную
      str += GSMport.read();    
      delay(20);   
   }   
   str = "<<< " + str;   
   return str;
}  
//Процедура отправки данных на сервер
void gprs_send(String dataa, String datab) {
   //отправка данных на сайт   
   String tempstr;   
 
   Serial.println("Send start");   
   GSMport.println("AT+HTTPINIT");   
   delay(1000);
   Serial.println(ReadGSM());
   GSMport.println("AT+HTTPPARA=\"CID\",1");
   delay(1000);
   Serial.println(ReadGSM());
   Serial.println("setup url");
   tempstr = String("AT+HTTPPARA=\"URL\",\"yoursite.ru/gps/write.php?lat=" +
       dataa + "&lon=" + datab +"\"");
   GSMport.println(tempstr);
   Serial.println(tempstr);
   delay(4000);
   Serial.println(ReadGSM());
   Serial.println("GET url");
   GSMport.println("AT+HTTPACTION=0");
   delay(5000);
   Serial.println(ReadGSM());
   Serial.println("Send done");
   GSMport.println("AT+HTTPTERM");
   delay(200);
   Serial.println(ReadGSM());
}
