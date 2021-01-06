#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN 9
#define SS_PIN 10

Servo servo;

byte LecturaUID[4];
byte aco[4] = {0x41, 0x21, 0x62, 0xA3};//ID ACO

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  //Serial.println("Listo ");
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);
  servo.attach(A0);
  servo.write(0);
  delay(3000);
  servo.write(0);
}

void loop() {
    if(! mfrc522.PICC_IsNewCardPresent())
      return;

  if (! mfrc522.PICC_ReadCardSerial())
      return;

  //Serial.print("UID:");
  for(byte i=0; i<mfrc522.uid.size; i++)
  {
    //if(mfrc522.uid.uidByte[i] < 0x10)
    //{
      //Serial.print(" 0");
      
    //}else
    //{
      //Serial.print(" ");
    //}
    //Serial.print(mfrc522.uid.uidByte[i],HEX);
    LecturaUID[i]=mfrc522.uid.uidByte[i];
  }

//Serial.print("\t");
if(comparaUID(LecturaUID, aco))
{
  Serial.println("Hola ACO");
}
else
{
  Serial.println("Acceso denegado");
}
mfrc522.PICC_HaltA();
}

boolean comparaUID(byte lectura[],byte usuario[])
{
  for(byte i=0; i<mfrc522.uid.size;i++)
  {
    if(lectura[i]!=usuario[i])
    {
      digitalWrite(7,HIGH);
      digitalWrite(4,HIGH);
      delay(300);
      digitalWrite(4,LOW);
      delay(100);
      digitalWrite(4,HIGH);
      delay(300);
      digitalWrite(4,LOW);
      delay(100);
      digitalWrite(4,HIGH);
      delay(300);
      digitalWrite(4,LOW);
      delay(100);
      digitalWrite(7,LOW);
      
      return false;
    }
    servo.write(180);
    digitalWrite(6,HIGH);   
    delay(2000);
    digitalWrite(6,LOW);
    servo.write(0);
    return true;
  }
}
