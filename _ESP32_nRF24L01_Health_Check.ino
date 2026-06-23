#include <SPI.h>

#define CE 4
#define CSN 5

void setup() {
  Serial.begin(115200);
  delay(3000); 
  Serial.println("\n====================================");
  Serial.println("--- Starting nRF24L01 Module Test ---");
  Serial.println("====================================");
  
  pinMode(CE, OUTPUT);
  pinMode(CSN, OUTPUT);
  
  digitalWrite(CSN, HIGH);
  digitalWrite(CE, LOW);
  
  // Explicitly tie hardware SPI pins
  SPI.begin(18, 19, 23, CSN);
  delay(100);
  
  // STEP 1: Clear the internal error/overflow flags (0x3F -> 0x0E)
  digitalWrite(CSN, LOW);
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  
  // 0x27 is the "Write to Register 0x07" command
  SPI.transfer(0x27); 
  // 0x70 writes logic high to bits 4, 5, and 6 to clear the status flags
  SPI.transfer(0x70); 
  
  SPI.endTransaction();
  digitalWrite(CSN, HIGH);
  
  delay(10); // Short pause to let registers write cleanly

  // STEP 2: Read the true status using a standard NOP (0xFF) instruction
  Serial.println("Reading active module status...");
  
  digitalWrite(CSN, LOW);
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  
  // NOP instruction forces the chip to shift out its status instantly
  uint8_t status = SPI.transfer(0xFF); 
  
  SPI.endTransaction();
  digitalWrite(CSN, HIGH);
  
  // STEP 3: Diagnose the Module Health
  Serial.print("Returned Status Byte: 0x");
  if (status < 0x10) Serial.print("0"); 
  Serial.println(status, HEX);
  
  Serial.println("\n------------- DIAGNOSIS -------------");
  if (status == 0x0E || status == 0x00) {
    Serial.println("✅ MODULE HEALTHY & READY!");
    Serial.println("SPI lines are responsive and buffers are clear.");
  } else if (status == 0xFF) {
    Serial.println("❌ CONNECTION ERROR (0xFF)");
    Serial.println("Check physical pin seating, ground, or MISO line.");
  } else if (status == 0x03) {
    Serial.println("❌ POWER ERROR (0x03 / 0x00)");
    Serial.println("The chip is responding but voltage is unstable.");
  } else {
    Serial.print("⚠️ ATTENTION: Status is 0x");
    Serial.println(status, HEX);
    Serial.println("Chip is alive, but flags failed to clear. Try resetting.");
  }
  Serial.println("-------------------------------------");
  Serial.println("Done.\n");
}

void loop() {
  // Empty
}
