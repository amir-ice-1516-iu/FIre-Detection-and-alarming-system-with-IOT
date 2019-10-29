#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;
int buzz = D8;
int motor=D4;
int gasPin = A0;
int frequency = 2500;
char auth[] = "tg8Z-Uqo1QpYHQfSNHOnVjs32Cce7VjW";

char ssid[] = "ICT_Innovation_Lab";
char pass[] = "beinnovative#";
//char ssid[] = "myphone";
//char pass[] = "lostworld";

int flag=0;
int k=0,p=0;
int isButtonPressed;
BLYNK_WRITE(V1) 
{
    k = param.asInt();
    if (k == 1){
//      noTone(buzz);
    analogWrite(buzz,0);
    }
    else if (k==0){
//      tone(buzz, frequency, 20);
    analogWrite(buzz, 200);
    }
}


void notifyOnFire(){
  isButtonPressed = digitalRead(D0);
  p = analogRead(gasPin);
  Blynk.virtualWrite(V2, p);
  Serial.print(" Sensor Value = ");
  Serial.println(isButtonPressed);
  if (isButtonPressed==0 && flag==0){
    Serial.println("Fire in the House");
    Blynk.notify("Alert : Fire in the House");
    flag=1;
//    tone(buzz, frequency, 200);
    analogWrite(buzz,200);
    digitalWrite(motor,HIGH);
  }
  else if (isButtonPressed==1){
    flag=0;
//    noTone(buzz);
//  analogWrite(buzz,0);
//  digitalWrite(motor,LOW);
  }
}

void setup(){
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(D0,INPUT_PULLUP);
  pinMode(motor,OUTPUT);
  pinMode(gasPin,INPUT);
  pinMode(buzz,OUTPUT);
  timer.setInterval(1000,notifyOnFire); 
}



void loop() {
  Blynk.run();
  timer.run();
  if (k==1 || isButtonPressed==0){
   analogWrite(buzz,200);
   digitalWrite(motor,HIGH);}
  else{
   analogWrite(buzz,0);
   digitalWrite(motor,LOW);}
//   tone(buzz, frequency, 20); 
}
