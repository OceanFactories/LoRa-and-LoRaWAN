#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

static const PROGMEM u1_t NWKSKEY[16] = { FILLMEIN }; <-- Change this address for every node!
static const u1_t PROGMEM APPSKEY[16] = { FILLMEIN };  <-- Change this address for every node!
static const u4_t DEVADDR = 0xFILLMEIN ; // <-- Change this address for every node!

void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

static osjob_t sendjob;

const unsigned TX_INTERVAL = 30;

// Pin mapping MAPPI32 <-- Change this address for every node board!
const lmic_pinmap lmic_pins = {
    .nss = 15,             // Pin NSS
    .rxtx = LMIC_UNUSED_PIN,  // Pin RX/TX control (Tergantung pada penggunaan)
    .rst = 0,              // Pin Reset
    .dio = {27, 2, 4}      // Pins DIO0, DIO1, DIO2
};



//AHT10 sensor 
#include <Adafruit_AHTX0.h>
Adafruit_AHTX0 aht;

float tem_data = 0, hum_data = 0;
const int ledPin=32;

// payload
byte payload[8];


void onEvent (ev_t ev) {
  Serial.print(os_getTime());
  Serial.print(": ");
  switch (ev) {
    case EV_SCAN_TIMEOUT:
      Serial.println(F("EV_SCAN_TIMEOUT"));
      break;
    case EV_BEACON_FOUND:
      Serial.println(F("EV_BEACON_FOUND"));
      break;
    case EV_BEACON_MISSED:
      Serial.println(F("EV_BEACON_MISSED"));
      break;
    case EV_BEACON_TRACKED:
      Serial.println(F("EV_BEACON_TRACKED"));
      break;
    case EV_JOINING:
      Serial.println(F("EV_JOINING"));
      break;
    case EV_JOINED:
      Serial.println(F("EV_JOINED"));
      break;
    case EV_RFU1:
      Serial.println(F("EV_RFU1"));
      break;
    case EV_JOIN_FAILED:
      Serial.println(F("EV_JOIN_FAILED"));
      break;
    case EV_REJOIN_FAILED:
      Serial.println(F("EV_REJOIN_FAILED"));
      break;
    case EV_TXCOMPLETE:
      Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
      if (LMIC.txrxFlags & TXRX_ACK)
        Serial.println(F("Received ack"));
      if (LMIC.dataLen) {
        Serial.println(F("Received "));
        Serial.println(LMIC.dataLen);
        Serial.println(F(" bytes of payload"));
        Serial.println("Received payload >> ");
        for (int i = 0; i < LMIC.dataLen; i++)
        {
          if (LMIC.frame[LMIC.dataBeg + i] < 0x10)
          {
            Serial.print("0" + String(LMIC.frame[LMIC.dataBeg + i], HEX) + " ");
          }
          else
          {
            Serial.print(String(LMIC.frame[LMIC.dataBeg + i], HEX) + " ");
          }
        }
        Serial.println("<< received payload");
      }
      // Schedule next transmission
      os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(TX_INTERVAL), do_send);
      break;
    case EV_LOST_TSYNC:
      Serial.println(F("EV_LOST_TSYNC"));
      break;
    case EV_RESET:
      Serial.println(F("EV_RESET"));
      break;
    case EV_RXCOMPLETE:
      // data received in ping slot
      Serial.println(F("EV_RXCOMPLETE"));
      break;
    case EV_LINK_DEAD:
      Serial.println(F("EV_LINK_DEAD"));
      break;
    case EV_LINK_ALIVE:
      Serial.println(F("EV_LINK_ALIVE"));
      break;
    default:
      Serial.println(F("Unknown event"));
      break;
  }
}

void do_send(osjob_t* j) {
  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println(F("OP_TXRXPEND, not sending"));
  } else {
    // Prepare upstream data transmission at the next possible time.

    Serial.println();
    Serial.println();
    aht10_read();
    createPayload();
    sendData();

    Serial.println(F("Packet queued"));
  }
  // Next TX is scheduled after TX_COMPLETE event.
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("Starting"));
  Wire.begin();
  aht10_init();
    pinMode(ledPin, OUTPUT);

  SPI.begin(14, 12, 13, 15);

#ifdef VCC_ENABLE
  pinMode(VCC_ENABLE, OUTPUT);
  digitalWrite(VCC_ENABLE, HIGH);
  delay(1000);
#endif

  // LMIC init
  os_init();
  // Reset the MAC state. Session and pending data transfers will be discarded.
  LMIC_reset();
  // Set static session parameters. Instead of dynamically establishing a session
  // by joining the network, precomputed session parameters are be provided.
#ifdef PROGMEM
  // On AVR, these values are stored in flash and only copied to RAM
  // once. Copy them to a temporary buffer here, LMIC_setSession will
  // copy them into a buffer of its own again.
  uint8_t appskey[sizeof(APPSKEY)];
  uint8_t nwkskey[sizeof(NWKSKEY)];
  memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
  memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
  LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);
#else
  // If not running an AVR with PROGMEM, just use the arrays directly
  LMIC_setSession (0x1, DEVADDR, NWKSKEY, APPSKEY);
#endif

#if defined(CFG_as923)
    // Setup channels for AS923_2 region
    LMIC_setupChannel(0, 921600000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);     
    LMIC_setupChannel(1, 922400000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);     
    LMIC_setupChannel(2, 921200000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);     
    LMIC_setupChannel(3, 921400000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);     
    LMIC_setupChannel(4, 921600000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);     
    LMIC_setupChannel(5, 921800000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);     
    LMIC_setupChannel(6, 922000000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);     
    LMIC_setupChannel(7, 922200000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);     
    LMIC_setupChannel(8, 922400000, DR_RANGE_MAP(DR_FSK, DR_FSK), BAND_MILLI);      
#elif defined(CFG_us915)
  LMIC_selectSubBand(1);
#endif

  // Disable link check validation
  LMIC_setLinkCheckMode(0);

  // TTN uses SF9 for its RX2 window.
  LMIC.dn2Dr = DR_SF9;

  // Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
  LMIC_setDrTxpow(DR_SF7, 20);
  LMIC_setClockError(MAX_CLOCK_ERROR * 10 / 100);
  // Start job
  do_send(&sendjob);
}

void loop() {
  os_runloop_once();


}
