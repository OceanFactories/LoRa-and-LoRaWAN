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
  long uvA_Long = uvA;
  long uvB_Long = uvB;
  long uvIndex_Long = uvIndex;

  payload[0] = (byte) ((suhuLong & 0X000000FF)       );
  payload[1] = (byte) ((kelembabanLong & 0X000000FF)       );
  payload[2] = (byte) ((uvA_Long & 0X000000FF)       );
  payload[3] = (byte) ((uvB_Long & 0X000000FF)       );
  payload[4] = (byte) ((uvIndex_Long & 0X000000FF)       );
}
