void drawOLED() {
  // Clear the display
  display.clearDisplay();

  // Set text size, color, and position
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // White text
  display.setCursor(0, 0);     // Start at the top-left corner

// Display your information
display.print("RSSI: ");
display.print(LMIC.rssi);
display.println(" dBm");

display.print("SNR: ");
display.print(LMIC.snr);
display.println(" dB");

// if (LMIC.txrxFlags & TXRX_ACK) {
  //  display.print("Data Send Status: Failure");
//  }
display.print("Send Status: ");
display.println(LMIC.txrxFlags & TXRX_ACK ? "Failure" : "Waiting");
display.println("Packets Sent: " + String(packetSent));
  // Display the temperature and humidity if available
  display.print("Temperature: ");
  display.print(tem_data);
  display.println(" C");

  display.print("Humidity: ");
  display.print(hum_data);
  display.println(" %");

  

  // You can add more information as needed

  // Display the updated information
  display.display();
}
