void sendData()
{
  Serial.println("Send Data");
  Serial.print("mydata >> ");
  for (int i = 0; i < sizeof(mydata); i++)
  {
    if (mydata[i] < 0x10)
    {
      Serial.print("0" + String(mydata[i], HEX) + " ");
    }
    else
    {
      Serial.print(String(mydata[i], HEX) + " ");
    }
  }
  Serial.println(" << mydata");
  LMIC_setTxData2(1, mydata, sizeof(mydata), 0);

}


void createPayload()
{
sensors_event_t humi, temp;
aht.getEvent(&humi, &temp);
Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" °C");
Serial.print("Humidity: "); Serial.print(humi.relative_humidity); Serial.println(" % RH");

float flat = gps.location.lat();
float flon = gps.location.lng();
float ahtSuhu = temp.temperature;
float ahtHumi = humi.relative_humidity;

char charLat[20];
char charLong[20];
char charAhtSuhu[6]; // Panjang karakter untuk suhu (total_width = 4)
char charAhtHumi[6]; // Panjang karakter untuk kelembaban (total_width = 4)

Serial1.print("Cords: ");
Serial1.print(flat); Serial1.print(" , ");
Serial1.println(flon);
dtostrf(flat, 10, 7, charLat);
dtostrf(flon, 10, 7, charLong);

// Menggunakan dtostrf untuk membatasi angka desimal suhu dan kelembaban
dtostrf(ahtSuhu, 4, 2, charAhtSuhu);
dtostrf(ahtHumi, 4, 2, charAhtHumi);

sprintf((char *)mydata, "%s,%s,%s,%s", charLat, charLong, charAhtSuhu, charAhtHumi);

}



