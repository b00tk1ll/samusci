#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "samusci-d0e8e.firebaseio.com"
#define FIREBASE_AUTH "8DlAybHXmYgYuxrvU30lXY1jS2Nz9HfywptT2pAY" //cloque aqui a autenticaçao para acessar o FIREBASE
#define WIFI_SSID "Android2" //coloque aqui o nome da rede que se deseja conectar
#define WIFI_PASSWORD "nocuuuuu"

#define pino_bomba D1
#define pino_energia_sensor D0
#define pino_leitura_sensor A0

void setupWIFI(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

// METODO de conexao FIREBASE
void setupFirebase(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  setupWIFI();
  setupFirebase();

  pinMode(pino_bomba,OUTPUT);
  pinMode(pino_energia_sensor,OUTPUT);
  pinMode(pino_leitura_sensor,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pino_energia_sensor,HIGH);

  Firebase.getBool("lamp");
  Serial.print("lamp: ");
  Serial.println(Firebase.getBool("lamp"));

  medir();

  if( Firebase.getBool("lamp") == true ){
    digitalWrite(pino_bomba,HIGH);
  }else if( Firebase.getBool("lamp") == false ){
    digitalWrite(pino_bomba,LOW);
  }
 
  //delay(1000);
  
  
}


void medir(){

  float valor_sensor = analogRead(pino_leitura_sensor); // 0 a 1024
  float plot = ((valor_sensor-530)*0.5*0.2 );
  float p1 = 100 - (plot*2.4);
  Serial.print("Sensor: ");
  //Serial.println(plot*2.35);
  if(p1 < 0){
    p1 = 0;
  }if(p1 > 100){
    p1 = 100;
  }
  
  Serial.println(p1);
  Firebase.push("humidity", p1);
  delay(1000);
}
