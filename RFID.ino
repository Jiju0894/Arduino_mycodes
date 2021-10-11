/*
  PINOUT:
  RC522 MODULE    Uno/Nano     MEGA
  SDA             D10          D9
  SCK             D13          D52
  MOSI            D11          D51
  MISO            D12          D50
  IRQ             N/A          N/A
  GND             GND          GND
  RST             D9           D8
  3.3V            3.3V         3.3V
*/
/* Include the standard Arduino SPI library */
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

void setup()
{
  Serial.begin(9600);
  /* Enable the SPI interface */
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

void loop()
{
  left = digitalRead(IR1);
  right = digitalRead(IR2);
  while (Serial.available())
  {
    state = Serial.read();
    Serial.println(state);
  }

  if (state == 'a')
  {
    
    /* Has a card been detected? */
    if (RC522.isCard())
    {
      /* If so then get its serial number */
      RC522.readCardSerial();
      Serial.println("Card detected:");
      Serial.println("-------STOP-----");
      //state='\0';
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      digitalWrite(M3, LOW);
      digitalWrite(M4, LOW);
      delay(1000);

      str2 = char('b');
      Serial.println(str2);
      state='\0';
      //    for(int i=0;i<5;i++)
      //    {
      //    Serial.print(RC522.serNum[i],DEC);
      //    //Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
      //    }
      Serial.println();
      Serial.println();
    }
    else
    {
      Serial.println("Card Not detected");
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
