/* 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 */
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define RST_PIN 9
#define SS_PIN 10

byte readCard[4];
String AllowedTag = "80B01121";  // REPLACE this Tag ID with your Tag ID!!!
String tagID = "";

#define RED_LED 3
#define GREEN_LED 4
// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  
  lcd.clear();
  lcd.print(" Access   ");
  lcd.setCursor(0, 1);
  lcd.print("Scan RFID Card >");

  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
}

void loop() {
  while (getID()) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    
    if (tagID == AllowedTag) 
    {
      
      lcd.print(" Access Granted!");
      lcd.setCursor(0, 1);
      lcd.print(" Welcome Back!! ");
      digitalWrite(GREEN_LED,HIGH);
      // You can write any code here like opening doors, switching relays, etc.
    }
    else
    {
      lcd.print(" Access Denied!");
      lcd.setCursor(0, 1);
      lcd.print("Card Not Valid!");
      digitalWrite(RED_LED,HIGH);
      //lcd.print(tagID);
    }
    
      Serial.println(tagID);
      
      delay(2000);
      digitalWrite(RED_LED,LOW);
      digitalWrite(GREEN_LED,LOW);
      lcd.clear();
      lcd.print("  Access   ");
      lcd.setCursor(0, 1);
      lcd.print("Scan RFID Card >");
  }
}

//Read new tag if available
boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}
