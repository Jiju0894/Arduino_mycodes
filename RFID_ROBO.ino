#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 10
#define RESET_DIO 9

#define IR1 6
#define IR2 7
#define M1 5
#define M2 4
#define M3 3
#define M4 2
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO);

int left, right;
char state;
bool flag = 0;
char str2;
char ack, data;
int x = 0;
//String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  SPI.begin();
  /* Initialise the RFID reader */
  RC522.init();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
}

void loop() {
  
  left = digitalRead(IR1);
  right = digitalRead(IR2);
  // print the string when a newline arrives:
  if (stringComplete)
  {
    Serial.println(state);
    if (RC522.isCard())
    {
      /* If so then get its serial number */
      RC522.readCardSerial();
      Serial.println("Card detected:");
      delay(500);
      Serial.println("-------STOP-----");
      //state='\0';
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      digitalWrite(M3, LOW);
      digitalWrite(M4, LOW);
      delay(1000);

      str2 = char('b');
      Serial.println(str2);
      delay(4000);
    // clear the string:
    state = '\0';
    stringComplete = false;
  }

  else
  {
    if ((left == 0) && (right == 0))
      {
        Serial.println("-------FORWARD-----");
        digitalWrite(M1, HIGH);
        digitalWrite(M2, LOW);
        digitalWrite(M3, HIGH);
        digitalWrite(M4, LOW);
      }

      if ((left == 1) && (right == 0))
      {
        Serial.println("------LEFT-----");
        digitalWrite(M1, HIGH);
        digitalWrite(M2, LOW);
        digitalWrite(M3, LOW);
        digitalWrite(M4, HIGH);
      }

      if ((left == 0) && (right == 1))
      {
        Serial.println("-------RIGHT-----");
        digitalWrite(M1, LOW);
        digitalWrite(M2, HIGH);
        digitalWrite(M3, HIGH);
        digitalWrite(M4, LOW);
      }

      if ((left == 1) && (right == 1))
      {
        Serial.println("-------STOP-----");
        digitalWrite(M1, LOW);
        digitalWrite(M2, LOW);
        digitalWrite(M3, LOW);
        digitalWrite(M4, LOW);
      }
  }
}
}

void serialEvent() {
  while (Serial.available())
  {
    // get the new byte:
    char state = Serial.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (state == 'a')
    {
      int i=1;
      stringComplete = true;
    }
    
    else
    {
      stringComplete = true;
      // add it to the inputString:
    //inputString += inChar;
    }
  }
}


