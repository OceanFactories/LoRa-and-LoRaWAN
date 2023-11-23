/*void bacaSensorUdara()
{
  // Menghasilkan suhu dan kelembaban acak antara 0 hingga 100
  suhu = random(30, 80);
  kelembaban = random(0, 100);
  Serial.println("T = " + String(suhu) + " °C | H = " + String(kelembaban) + " %RH");
}*/
void aht10_init()
{
  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(1000);
  }
}

void aht10_read()
{
  Serial.println("Read AHT10 Sensor...");
  delay(1000);
}

void bacaSensorUV()
{
  // Menghasilkan nilai UV A, UV B, dan UV Index acak antara 0 hingga 100
  uvA = random(0, 100);
  uvB = random(0, 100);
  uvIndex = random(0, 100);
  
  Serial.println("UV A = " + String(uvA) + " µW/cm2 | UV B = " + String(uvB) + " µW/cm2 | UV Index = " + String(uvIndex));
}
