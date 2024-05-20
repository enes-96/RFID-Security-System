#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 21   
#define RST_PIN 22  
#define SERVO_PIN 23  

MFRC522 mfrc522(SS_PIN, RST_PIN); 
Servo servo; // 

void setup() {
  Serial.begin(9600);  
  SPI.begin(); 
  mfrc522.PCD_Init(); 

  servo.attach(SERVO_PIN); 
  servo.write(0);
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String rfidTag = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTag += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      rfidTag += String(mfrc522.uid.uidByte[i], HEX);
    }
    mfrc522.PICC_HaltA(); 

    if (rfidTag == "YOUR_AUTHORIZED_RFID_TAG") {
      Serial.println("Access granted!"); 
      servo.write(90); 
      delay(2000);
      servo.write(0); 
    } else {
      Serial.println("Access denied!"); 
    }
  }
}
