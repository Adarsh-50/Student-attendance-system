#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10  // Define the chip select pin for the RFID reader
#define RST_PIN 3 // Define the reset pin for the RFID reader

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
    Serial.begin(9600); // Initialize serial communication
    SPI.begin(); // Initialize SPI bus
    mfrc522.PCD_Init(); // Initialize MFRC522 RFID module
    Serial.println("RFID reader initialized.");
    Serial.println("Place your card :");
}

void loop() {
    // Look for new RFID cards
    readsuccess = getid();
    if(readsuccess)
    {
      Serial.println( (String) "DATA,DATE,TIME," + StrUID );
    }
}

int getid(){  
  if(!mfrc522.PICC_IsNewCardPresent()){
    return 0;
  }
  if(!mfrc522.PICC_ReadCardSerial()){
    return 0;
  }
 
  
  Serial.println("THE UID OF THE SCANNED CARD IS:");
  
  for(int i=0;i<4;i++){
    readcard[i]=mfrc522.uid.uidByte[i]; //storing the UID of the tag in readcard
    array_to_string(readcard, 4, str);
    StrUID = str;
  }
  mfrc522.PICC_HaltA();
  return 1;
}
// --------------------------------------------------------------------
void array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}
