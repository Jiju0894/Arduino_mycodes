#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
RTC_DS1307 RTC;
#include<EEPROM.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1);
//#include<Servo.h>
int tmp, Inc, hor, mIn, add = 0;
int set = 8;  //time setting enable
int cge = 9;  //increment
int mod = 10;  //mode setting
int off = 0;
int ch, cm;
int Hor = 0, Min = 0, Sec = 0;
//int relaypin=A0;
//int relaypin1=5;
int x=0;
int y=0;
int z=0;
int buzzer=A3;
int count1, count2, count3, count4, count5, count6, count7, count8, count9, count10;
int light_m1=13, light_m2=12,light_m3=11;
//int count1, count2, count3, count4, count5, count6, count7, count8, count9, count10;
const int med1_voice=A0, med2_voice = A1, med3_voice= A2;

void setup ()
{
  Serial.begin(9600);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module 
  delay(100);
  Wire.begin();
  RTC.begin();
  lcd.begin(16, 2);
   pinMode(light_m1, OUTPUT);
  pinMode(light_m2, OUTPUT);
  pinMode(light_m3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(med1_voice, OUTPUT);
  pinMode(med2_voice, OUTPUT);
  pinMode(med3_voice, OUTPUT);
//  pinMode(m1,OUTPUT);
//    pinMode(m2,OUTPUT);
  //motor.attach(6);
  pinMode(set, INPUT_PULLUP);
  pinMode(cge, INPUT_PULLUP);
  pinMode(mod, INPUT_PULLUP);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("MEDICINE BOX");
   lcd.setCursor(0, 1);
  lcd.print("REMINDER");
  delay(3000);
   //RTC.adjust(DateTime(2021, 2, 8, 11, 47, 00));
 RTC.adjust(DateTime(F(__DATE__), F( __TIME__)));
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
   //RTC.adjust(DateTime(F(__DATE__), F( __TIME__)));
  //  RTC.adjust(DateTime(2021, 2, 8, 11, 37, 00));

  }
  digitalWrite(set, HIGH);
  digitalWrite(cge, HIGH);
  digitalWrite(mod, HIGH);



 digitalWrite(light_m1, LOW);
 digitalWrite(light_m2, LOW);
 digitalWrite(light_m3, LOW);
 digitalWrite(buzzer, LOW);

 digitalWrite(med1_voice,HIGH);
 digitalWrite(med2_voice,HIGH);
 digitalWrite(med3_voice,HIGH);
//  digitalWrite(relaypin,LOW);
//  digitalWrite(relaypin1,LOW); 
  
  //motor.write(0);

}

void loop ()
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Date:");
  lcd.setCursor(0, 1);
  lcd.print("Time:");
  DateTime now = RTC.now();
  lcd.setCursor(5, 0);
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);
  lcd.print(' ');
  lcd.setCursor(5, 1);
  if (now.hour() < 10)
    lcd.print('0');
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  if (now.minute() < 10)
    lcd.print('0');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  if (now.second() < 10)
    lcd.print('0');
  lcd.print(now.second(), DEC);
  delay(1000);
  ch = now.hour();
  cm = now.minute();
  Serial.print("ch");
  Serial.print(ch);
  Serial.print("\tcm");
  Serial.println(cm);
  if (digitalRead(mod) == LOW)
  {
    settime();
  }
  Checktime();
  Serial.print("Hor:");
  Serial.print(EEPROM.read(1));
  Serial.print("\tmin:");
  Serial.println(EEPROM.read(2));
  Serial.print("mHor:");
  Serial.print(Hor);
  Serial.print("\tm-min:");
  Serial.println(mIn);
}

void settime()
{

  int i = 0;
  int tmp = 1;

  //////////////////Morning food ON TIME
  while (tmp == 1)
  {
    off = 0;
    if (digitalRead(cge) == 0)
    {
      Hor++;
      if (Hor == 24)
      {
        Hor = 0;
      }
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("First Medicine:");
    lcd.setCursor(0, 1);
    if (Hor < 10)
    {
      lcd.print("0");
    lcd.print("");
    lcd.print(Hor);
    lcd.print(":");
    lcd.print("0");
    lcd.print("");
    lcd.print(Min);
    lcd.print(":");
    lcd.print("0");
    lcd.print(Sec);
    delay(500);
    }
    if ((digitalRead(set) == 0) && (i == 0))                            //alarm1_hour
    {

      hor = Hor;
      EEPROM.write(1, hor);
      Serial.println(EEPROM.read(1));
      i++;
      tmp = 2;
      while (digitalRead(set) == 0);
    }
    while (tmp == 2)
    {
      if (digitalRead(cge) == 0)
      {
        Min++;
        if (Min == 60)
        {
          Min = 0;
        }
      }
      lcd.setCursor(0, 1);
      lcd.print("0");
      lcd.print("");
      lcd.print(Hor);
      lcd.print(":");
      lcd.print("");
      lcd.print(Min);
      lcd.print(":");
      lcd.print("0");
      lcd.print(Sec);
      delay(200);

      if ((digitalRead(set) == 0) && (i == 1))                           //alarm1_min
      {
        mIn = Min;
        EEPROM.write(2, mIn);
        Serial.println(EEPROM.read(2));
        i++;
        Serial.println("alarm1 time is set ");
        tmp = 3;
        while (digitalRead(set) == 0);
      }
    }
  }


  ///////////////Morning food OFF TIME

  while (tmp == 3)
  {
    off = 0;
    if (digitalRead(cge) == 0)
    {
      Hor++;
      if (Hor == 24)
      {
        Hor = 0;
      }
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Second Medicine:");
    lcd.setCursor(0, 1);
    if (Hor < 10)
      lcd.print("0");
    lcd.print("");
    lcd.print(Hor);
    lcd.print(":");
    lcd.print("0");
    lcd.print("");
    lcd.print(Min);
    lcd.print(":");
    lcd.print("0");
    lcd.print(Sec);
    delay(500);

    if ((digitalRead(set) == 0) && (i == 2))                            //alarm1_hour
    {
      Serial.println("Bulb off time set");
      hor = Hor;
      EEPROM.write(3, hor);
      Serial.println(EEPROM.read(3));
      i++;
      tmp = 4;
      while (digitalRead(set) == 0);
    }
    while (tmp == 4)
    {
      if (digitalRead(cge) == 0)
      {
        Min++;
        if (Min == 60)
        {
          Min = 0;
        }
      }
      lcd.setCursor(0, 1);
      lcd.print("0");
      lcd.print("");
      lcd.print(Hor);
      lcd.print(":");
      lcd.print("");
      lcd.print(Min);
      lcd.print(":");
      lcd.print("0");
      lcd.print(Sec);
      delay(200);

      if ((digitalRead(set) == 0) && (i == 3))                           //alarm1_min
      {
        mIn = Min;
        EEPROM.write(4, mIn);
        Serial.println(EEPROM.read(4));
        i++;
        Serial.println("Bulb Off time is set ");
        tmp = 5;
        while (digitalRead(set) == 0);
      }
    }
  }
  ////////////////////  Lunch ON TIME
  while (tmp == 5)
  {
    off = 0;
    if (digitalRead(cge) == 0)
    {
      Hor++;
      if (Hor == 24)
      {
        Hor = 0;
      }
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Third Medicine:");

    lcd.setCursor(0, 1);
    if (Hor < 10)
      lcd.print("0");
    lcd.print("");
    lcd.print(Hor);
    lcd.print(":");
    lcd.print("0");
    lcd.print("");
    lcd.print(Min);
    lcd.print(":");
    lcd.print("0");
    lcd.print(Sec);
    delay(500);

    if ((digitalRead(set) == 0) && (i == 4))                            //alarm1_hour
    {
      Serial.println("Bulb ON time set");
      hor = Hor;
      EEPROM.write(5, hor);
      Serial.println(EEPROM.read(5));
      i++;
      tmp = 6;
      while (digitalRead(set) == 0);
    }
  
    while (tmp == 6)
    {
      if (digitalRead(cge) == 0)
      {
        Min++;
        if (Min == 60)
        {
          Min = 0;
        }
      }
      lcd.setCursor(0, 1);
      lcd.print("0");
      lcd.print("");
      lcd.print(Hor);
      lcd.print(":");
      lcd.print("");
      lcd.print(Min);
      lcd.print(":");
      lcd.print("0");
      lcd.print(Sec);
      delay(200);

      if ((digitalRead(set) == 0) && (i == 5))                           //alarm1_min
      {
        mIn = Min;
        EEPROM.write(6, mIn);
        Serial.println(EEPROM.read(6));
        i++;
        Serial.println("Bulb on time set");
        tmp = 7;
        while (digitalRead(set) == 0);
      }
    }
  }
  //////////////////////lunch OFF TIME

//  while (tmp == 7)
//  {
//    off = 0;
//    if (digitalRead(cge) == 0)
//    {
//      Hor++;
//      if (Hor == 24)
//      {
//        Hor = 0;
//      }
//    }
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("Fan off time");
//
//    lcd.setCursor(0, 1);
//    if (Hor < 10)
//      lcd.print("0");
//    lcd.print("");
//    lcd.print(Hor);
//    lcd.print(":");
//    lcd.print("0");
//    lcd.print("");
//    lcd.print(Min);
//    lcd.print(":");
//    lcd.print("0");
//    lcd.print(Sec);
//    delay(500);
//
//    if ((digitalRead(set) == 0) && (i == 6))                            //alarm1_hour
//    {
//      Serial.println("Fan OFF time set");
//      hor = Hor;
//      EEPROM.write(7, hor);
//      Serial.println(EEPROM.read(7));
//      i++;
//      tmp = 8;
//      while (digitalRead(set) == 0);
//    }
//    while (tmp == 8)
//    {
//      if (digitalRead(cge) == 0)
//      {
//        Min++;
//        if (Min == 60)
//        {
//          Min = 0;
//        }
//      }
//      lcd.setCursor(0, 1);
//      lcd.print("0");
//      lcd.print("");
//      lcd.print(Hor);
//      lcd.print(":");
//      lcd.print("");
//      lcd.print(Min);
//      lcd.print(":");
//      lcd.print("0");
//      lcd.print(Sec);
//      delay(200);
//
//      if ((digitalRead(set) == 0) && (i == 7))                           //alarm1_min
//      {
//        mIn = Min;
//        EEPROM.write(8, mIn);
//        Serial.println(EEPROM.read(8));
//        i++;
//        Serial.println("lunch ON time set");
//        tmp = 9;
//        while (digitalRead(set) == 0);
//      }
//    }
//  }
//  while (tmp == 9)
//  {
//    off = 0;
//    if (digitalRead(cge) == 0)
//    {
//      Hor++;
//      if (Hor == 24)
//      {
//        Hor = 0;
//      }
//    }
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("med3 on time");
//    lcd.setCursor(0, 1);
//    if (Hor < 10)
//      lcd.print("0");
//    lcd.print("");
//    lcd.print(Hor);
//    lcd.print(":");
//    lcd.print("0");
//    lcd.print("");
//    lcd.print(Min);
//    lcd.print(":");
//    lcd.print("0");
//    lcd.print(Sec);
//    delay(500);
//
//    if ((digitalRead(set) == 0) && (i == 8))                            //alarm1_hour
//    {
//
//      hor = Hor;
//      EEPROM.write(1, hor);
//      Serial.println(EEPROM.read(9));
//      i++;
//      tmp = 10;
//      while (digitalRead(set) == 0);
//    }
//    while (tmp == 10)
//    {
//      if (digitalRead(cge) == 0)
//      {
//        Min++;
//        if (Min == 60)
//        {
//          Min = 0;
//        }
//      }
//      lcd.setCursor(0, 1);
//      lcd.print("0");
//      lcd.print("");
//      lcd.print(Hor);
//      lcd.print(":");
//      lcd.print("");
//      lcd.print(Min);
//      lcd.print(":");
//      lcd.print("0");
//      lcd.print(Sec);
//      delay(200);
//
//      if ((digitalRead(set) == 0) && (i == 9))                           //alarm1_min
//      {
//        mIn = Min;
//        EEPROM.write(2, mIn);
//        Serial.println(EEPROM.read(10));
//        i++;
//        Serial.println("alarm1 time is set ");
//        tmp = 11;
//        while (digitalRead(set) == 0);
//      }
//    }
//  }
//
//
//  ///////////////Morning food OFF TIME
//
//  while (tmp == 11)
//  {
//    off = 0;
//    if (digitalRead(cge) == 0)
//    {
//      Hor++;
//      if (Hor == 24)
//      {
//        Hor = 0;
//      }
//    }
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("med3 off time");
//    lcd.setCursor(0, 1);
//    if (Hor < 10)
//      lcd.print("0");
//    lcd.print("");
//    lcd.print(Hor);
//    lcd.print(":");
//    lcd.print("0");
//    lcd.print("");
//    lcd.print(Min);
//    lcd.print(":");
//    lcd.print("0");
//    lcd.print(Sec);
//    delay(500);
//
//    if ((digitalRead(set) == 0) && (i == 10))                            //alarm1_hour
//    {
//      Serial.println("morn off time set");
//      hor = Hor;
//      EEPROM.write(3, hor);
//      Serial.println(EEPROM.read(11));
//      i++;
//      tmp = 12;
//      while (digitalRead(set) == 0);
//    }
//    while (tmp == 12)
//    {
//      if (digitalRead(cge) == 0)
//      {
//        Min++;
//        if (Min == 60)
//        {
//          Min = 0;
//        }
//      }
//      lcd.setCursor(0, 1);
//      lcd.print("0");
//      lcd.print("");
//      lcd.print(Hor);
//      lcd.print(":");
//      lcd.print("");
//      lcd.print(Min);
//      lcd.print(":");
//      lcd.print("0");
//      lcd.print(Sec);
//      delay(200);
//
//      if ((digitalRead(set) == 0) && (i == 11))                           //alarm1_min
//      {
//        mIn = Min;
//        EEPROM.write(4, mIn);
//        Serial.println(EEPROM.read(12));
//        i++;
//        Serial.println("M3 Off time is set ");
//        tmp = 13;
//        while (digitalRead(set) == 0);
//      }
//    }
 //}
  //////////////////// dinner ON TIME
 
  //////////////////////lunch OFF TIME

 
  off = 1;
}


//////////////////////////////GATE CLOSE TIME
void Checktime()
{
  int x=0,y=0,z=0;
  Serial.println("enter tcheck loop");

  /////Morn food ON time
  if ((ch == EEPROM.read(1) ) && ( cm == EEPROM.read(2) ))
  {
    count2 = 0; count6 = 0;
    count1 = count1 + 1;
    if (count1 < 2)
    {
      lcd.clear();
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      digitalWrite(light_m1, HIGH);
      lcd.setCursor(0,0);
      lcd.print("Take First");
      lcd.setCursor(0,1);
      lcd.print("Medicine");
     digitalWrite(med1_voice, LOW);
      delay(3000);
    digitalWrite(light_m1, HIGH);
    digitalWrite(med1_voice, HIGH);    
    }
//    lcd.clear();
//    lcd.print("TAKE FOOD");
    delay(1000);

  }

  ////////// Morn food off time
  if ((ch == EEPROM.read(3) ) && ( cm == EEPROM.read(4) ))
  {
//    lcd.clear();
//    lcd.print("Food closed");
//    delay(1000);
    count1 = 0;
    count2 = count2 + 1;
    if (count2 < 2)
    {
      lcd.clear();
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      digitalWrite(light_m2, HIGH);
      lcd.setCursor(0,0);
      lcd.print("Take Second");
      lcd.setCursor(0,1);
      lcd.print("Medicine");
     digitalWrite(med2_voice, LOW);
      delay(3000);
    digitalWrite(light_m2, HIGH);
    digitalWrite(med2_voice, HIGH);   
    }
    delay(1000);
  }
  ///////Lunch food ON time
  if ((ch == EEPROM.read(5) ) && ( cm == EEPROM.read(6) ))
  {
    count1 = 0; count2 = 0; //count6 = 0; count7 = 0;
    count3 = count3 + 1;
    if (count3 < 2)
    {
      lcd.clear();
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      digitalWrite(light_m3, HIGH);
      lcd.setCursor(0,0);
      lcd.print("Take First");
      lcd.setCursor(0,1);
      lcd.print("Medicine");
     digitalWrite(med3_voice, LOW);
      delay(3000);
    digitalWrite(light_m3, HIGH);
    digitalWrite(med3_voice, HIGH);   
    }
  
//    lcd.clear();
//    lcd.print("TAKE FOOD");
    delay(2000);

  }
  /////// Lunch off time
//  if ((ch == EEPROM.read(7) ) && ( cm == EEPROM.read(8) ))
//  {
////    lcd.clear();
////    lcd.clear();
////    lcd.print("Food closed");
////    delay(1000);
//    count3 = 0;count1=0;count2=0;
//    count4 = count4 + 1;
//    if (count4 < 2)
//    {
//      digitalWrite(relaypin1,LOW);
//    //  motor.write(0);
//      delay(1000);
//    }
//  }
  /////// dinner on time
//  if ((ch == EEPROM.read(9) ) && ( cm == EEPROM.read(10) ))
//  {
//    count4 = 0; count3 = 0;count2 = 0;count1 = 0;
//    count5 = count5 + 1;
//    if (count5 < 2)
//    {
//       Serial.println("time for med3");
//      //digitalWrite(m1,HIGH);
//     // motor.write(80);
//    
////         Serial.println("sending sms...");
////          mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
////
////          delay(1000);  // Delay of 1000 milli seconds or 1 second
////        
////          mySerial.println("AT+CMGS=\"+919885089823\"\r"); // Replace x with mobile number
////        
////          delay(1000);
////        
////          mySerial.println("med3 taking time");// The SMS text you want to send
////        
////          delay(100);
////        
////          mySerial.println((char)26);// ASCII code of CTRL+Z
////        
////          delay(1000);
////      delay(4000);
//    }
////    lcd.clear();
////    lcd.print("TAKE FOOD");
//    delay(2000);
//
//  }
//
//  ////////// Morn food off time
//  if ((ch == EEPROM.read(11) ) && ( cm == EEPROM.read(12) ))
//  {
////    lcd.clear();
////    lcd.print("Food closed");
////    delay(1000);
//    count5 = 0;count4 = 0;count3 = 0;count2 = 0;count1 = 0;
//    count6 = count6 + 1;
//    if (count6 < 2)
//    {
//     // digitalWrite(m1,LOW);
//     // motor.write(0);
//      delay(1000);
//    }
//  }

  }
