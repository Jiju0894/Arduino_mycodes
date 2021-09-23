#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define BUTTON1 7
#define BUTTON2 8
#define BUTTON3 6

int count = 0;                              // count = 0
char input[12];                                         // character array of size 12 
boolean flag = 0,temp=0;                                       // flag =0
//char id1[12]="B3 9F 55 16";
//char id2[12]="8A AF 95 1A";
//char id3[12]="3A 41 B7 1A";
//char id4[12]="9A AB 93 1A";
//char id4[12]="13 A5 DB 16";

const int rs = A5, en = A4, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int r=50;
int d=80;
int o=120;
int s=60;
int t=0;
int sa=20;

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(BUTTON1,INPUT_PULLUP);
   pinMode(BUTTON2,INPUT_PULLUP);
   pinMode(BUTTON3,INPUT_PULLUP);
   lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("RFID BASED SMART");
  lcd.setCursor(0,1);
  lcd.print("SHOPING TROLLEY");
  delay(6000);
  
}




void loop() 
{

 
//////////////////////////////////////////////////// TOTAL //////////////////////////////////////////////
 if(digitalRead(BUTTON3)==LOW)
     {
      flag=0;
      temp=0;
        Serial.println("End of Shopping");
        Serial.print("Total bill: ");
        Serial.println(t); 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("End of Shopping");
        lcd.setCursor(0,1);
        lcd.print("Total bill: ");
        lcd.print(t);
     }
////////////////////////////////////////////////// REMOVE ///////////////////////////////////////////////////////////

  if(digitalRead(BUTTON2)==LOW)
  {
    Serial.println("Removing ..");
     temp=1;
     flag=0;
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Removing..");
    delay(2000);
    lcd.clear();
  }
  if (temp==1)
  {
    
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B3 9F 55 16") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Removing Rice packet");
    //Serial.println();
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Remove Rice: ");
    lcd.print(r);
    t=t-r;
    delay(3000);
  }

  if (content.substring(1) == "8A AF 95 1A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Removing Dal packet");
    //Serial.println();
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Remove Dal: ");
    lcd.print(d);
    t=t-d;
    delay(3000);
  }

  if (content.substring(1) == "3A 41 B7 1A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Removing Oil packet");
    //Serial.println();
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Remove Oil: ");
    lcd.print(o);
    t=t-o;
    delay(3000);
  }
  
  if (content.substring(1) == "9A AB 93 1A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Removing Sugar packet");
    //Serial.println();
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Remove Sugar: ");
    lcd.print(s);
    t=t-s;
    delay(3000);
  }

  if (content.substring(1) == "13 A5 DB 16") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Removing Salt packet");
    //Serial.println();
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Remove Salt: ");
    lcd.print(sa);
    t=t-sa;
    delay(3000);
  }
  }

   ///////////////////////////////////////// ADD ////////////////////////////////////////////////////
  if(digitalRead(BUTTON1)==LOW)
  {
    Serial.println("Adding..");
     flag=1;
     temp=0;
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Adding..");
    delay(2000);
    lcd.clear();
  }
  if (flag==1)
  {
    
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B3 9F 55 16") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Rice packet Price = 50rs");
    //Serial.println();
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Rice: ");
    lcd.print(r);
    t=t+r;
    delay(3000);
  }

  if (content.substring(1) == "8A AF 95 1A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Dal packet Price = 80rs");
    //Serial.println();
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dal: ");
    lcd.print(d);
    t=t+d;
    delay(3000);
  }

  if (content.substring(1) == "3A 41 B7 1A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Oil packet Price = 200rs");
    //Serial.println();
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Oil: ");
    lcd.print(o);
    t=t+o;
    delay(3000);
  }
  
  if (content.substring(1) == "9A AB 93 1A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Sugar packet Price = 60rs");
    //Serial.println();
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sugar: ");
    lcd.print(s);
    t=t+s;
    delay(3000);
  }

  if (content.substring(1) == "13 A5 DB 16") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Salt packet Price = 20rs");
    //Serial.println();
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Salt: ");
    lcd.print(sa);
    t=t+sa;
    delay(3000);
  }
  }
}
