#include <SoftwareSerial.h>
#include <ezBuzzer.h>
SoftwareSerial bluetooth(8, 9); // RX, TX
int trigPin = 2;
int echoPin = 3;
float duration, distance;
const int mL1 = 7;
const int mL2 = 6;
const int mR1 = 5;
const int mR2 = 4;
const int buzzer_pin = 11;

char var;
ezBuzzer buzzer(buzzer_pin);
void setup() {

   pinMode(mL1, OUTPUT);
   pinMode(mL2, OUTPUT);
   pinMode(mR1, OUTPUT);
   pinMode(mR2, OUTPUT);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, OUTPUT);
   bluetooth.begin(9600);
   Serial.begin(9600);
}

void loop() {
buzzer.loop();
ultrasonic();

if(bluetooth.available()>0)
var=bluetooth.read();
Serial.println(var);
if(var=='F')
{
  if (distance<50)
  {
    stop_now();
    buzzer.beep(100);
  }
  else
  {
    forward();
  }
}
else if(var=='B')
{
  backward();
}
else if(var=='L')
{
  left();
}
else if(var=='R')
{
  right();
}
else{
  stop_now();
}
}
void right(){
  digitalWrite(mL1,LOW);
  digitalWrite(mL2,HIGH);
  digitalWrite(mR1,HIGH);
  digitalWrite(mR2,LOW);
}
void left(){
  digitalWrite(mL1,HIGH);
  digitalWrite(mL2,LOW);
  digitalWrite(mR1,LOW);
  digitalWrite(mR2,HIGH);
}
void stop_now(){
  digitalWrite(mL1,LOW);
  digitalWrite(mL2,LOW);
  digitalWrite(mR1,LOW);
  digitalWrite(mR2,LOW);
}
void forward(){
  digitalWrite(mL1,HIGH);
  digitalWrite(mL2,LOW);
  digitalWrite(mR1,HIGH);
  digitalWrite(mR2,LOW);
}
void backward(){
  digitalWrite(mL1,LOW);
  digitalWrite(mL2,HIGH);
  digitalWrite(mR1,LOW);
  digitalWrite(mR2,HIGH);
}
void ultrasonic(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*0.034)/2;
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
}
