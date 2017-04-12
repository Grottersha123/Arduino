



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
  }
}


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
makeCoords(N1, E1, N2, E2, 10);

}

void loop() {
  // put your main code here, to run repeatedly:

}
