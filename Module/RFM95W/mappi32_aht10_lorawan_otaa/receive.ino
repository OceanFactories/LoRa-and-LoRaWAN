void decodeDownlink(const byte* payload, size_t size) {
  String command = "";
  for (size_t i = 0; i < size; i++) {
    command += (char)payload[i];
  }
  
  Serial.print("Received command: ");
  Serial.println(command);

  if (command == "LED_ON") {
    Serial.println("Turning LED ON");
    digitalWrite(ledPin, HIGH); // Turn the LED on
  } else if (command == "LED_OFF") {
    Serial.println("Turning LED OFF");
    digitalWrite(ledPin, LOW); // Turn the LED off
  }
}