#include <Ultrasonic.h>
#define pino_trigger D7
#define pino_echo D6

int IN1 = D8;
int IN2 = D9;
int IN3 = D10;
int IN4 = D11;
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
}
 
void loop()
{
  float cm;
  long microsec = ultrasonic.timing();
  cm = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("Distancia em cm: ");
  Serial.println(cm);
  delay(1000);

  if(cm > 10){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}
