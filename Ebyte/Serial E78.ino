#include <HardwareSerial.h>

HardwareSerial SerialLoRa(2); 
void setup() {
  Serial.begin(115200); 
  SerialLoRa.begin(9600); 

  Serial.println("ESP32 AT Command Example");
  Serial.println("Ketik perintah AT dan tekan Enter untuk melihat responsnya.");
}

void loop() {
  
  if (Serial.available()) {
    char receivedChar = Serial.read();
    SerialLoRa.write(receivedChar); 

    
    if (receivedChar == '\n') {
      SerialLoRa.write('\r');
    }
  }

  
  if (SerialLoRa.available()) {
    char responseChar = SerialLoRa.read();
    Serial.print(responseChar);
  }
}
