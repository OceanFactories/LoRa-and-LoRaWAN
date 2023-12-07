void sendData()
{
  Serial.println("Send Data");
  Serial.print("payload >> ");
  for (int i = 0; i < sizeof(payload); i++)
  {
    if (payload[i] < 0x10)
    {
      Serial.print("0" + String(payload[i], HEX) + " ");
    }
    else
    {
      Serial.print(String(payload[i], HEX) + " ");
    }
  }
  Serial.println(" << payload");
  LMIC_setTxData2(1, payload, sizeof(payload), 0);
}

void createPayload()
{
  long suhuLong = tem_data;
  long kelembabanLong = hum_data;


  payload[0] = (byte) ((suhuLong & 0xFF000000) >> 24 );
  payload[1] = (byte) ((suhuLong & 0x00FF0000) >> 16 );
  payload[2] = (byte) ((suhuLong & 0x0000FF00) >> 8  );
  payload[3] = (byte) ((suhuLong & 0X000000FF)       );

  payload[4] = (byte) ((kelembabanLong & 0xFF000000) >> 24 );
  payload[5] = (byte) ((kelembabanLong & 0x00FF0000) >> 16 );
  payload[6] = (byte) ((kelembabanLong & 0x0000FF00) >> 8  );
  payload[7] = (byte) ((kelembabanLong & 0X000000FF)       );

}

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
