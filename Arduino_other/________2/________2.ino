
int PIN = 8;
int voted_1;
int val = 0;

void setup()
{
  pinMode(PIN,INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("MAMAMAMAMAMAM");
}

void loop()
{
  voted_1 = digitalRead(PIN);
  if (!voted_1){
    delay(50);

      if (!voted_1){
        do{
        }while(!digitalRead(PIN));
        Serial.println(val++);
        
      }
    }
    
  }

