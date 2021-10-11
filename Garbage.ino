#include<SoftwareSerial.h>
#include<Servo.h>

#define ECHO 6
#define TRIG 7
#define servoPin 5

Servo Servo1;
SoftwareSerial mySerial(9, 10);
int Tx = 10;
int Rx = 9;

int distance = 0;
long duration1 = 0;
char str1, str2;
char ack;
int i;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Servo1.attach(servoPin);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Servo1.write(0);
}

void loop()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration1 = pulseIn(ECHO, HIGH);
  distance = (duration1 * 0.034) / 2;

  //  Serial.print("Distance of garbage::");
  //  Serial.println(distance);
  //  delay(2000);
  str1 = char('a'); //+String(distance);
  str2 = char('c');

  if (distance < 10)
  {
    Serial.println(str1);
  }

  if (Serial.available())
  {
    ack = Serial.read();
    if (ack == 'b')
    {
      Serial.println("Shifting waste");
      Servo1.write(90);
      delay(3000);
      Servo1.write(0);
      delay(2000);
      Serial.println("Waste Collected");
      for (i = 0; i < 5; i++)
      {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(1000);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(1000);
      }

      //Serial.println(str2);
    }
  }
}
