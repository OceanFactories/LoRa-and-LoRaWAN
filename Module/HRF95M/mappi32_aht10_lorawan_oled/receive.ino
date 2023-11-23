void decodeDownlink(const byte* payload, size_t size) {
  String command = "";
  for (size_t i = 0; i < size; i++) {
    command += (char)payload[i];
  }

  if (command == "LED_ON") {
    digitalWrite(ledPin, HIGH); // Turn the LED on
  } else if (command == "LED_OFF") {
    digitalWrite(ledPin, LOW); // Turn the LED off
  }
}