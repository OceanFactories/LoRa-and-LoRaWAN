
void bacaSensorUV()
{
  // Menghasilkan nilai UV A, UV B, dan UV Index acak antara 0 hingga 100
  uvA = random(0, 100);
  uvB = random(0, 100);
  uvIndex = random(0, 100);
  
  Serial.println("UV A = " + String(uvA) + " µW/cm2 | UV B = " + String(uvB) + " µW/cm2 | UV Index = " + String(uvIndex));
}
