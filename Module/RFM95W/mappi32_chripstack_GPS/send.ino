/*void sendData()
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

}*/

void sendData(){
  LMIC_setTxData2(1, mydata,25, 0);
}

void createPayload()
{
float flat=gps.location.lat();
float flon=gps.location.lng();

char charLat[20];
char charLong[20];

Serial1.print("Cords: ");
Serial1.print(flat); Serial1.print(" , ");
Serial1.println(flon);
dtostrf(flat, 10, 7, charLat);
dtostrf(flon, 10, 7, charLong);
sprintf((char *)mydata, "%s,%sX", charLat,charLong);
}



