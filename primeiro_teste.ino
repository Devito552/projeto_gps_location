#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Defina os pinos para o SoftwareSerial
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// Crie uma instância do objeto TinyGPS++
TinyGPSPlus gps;

// Crie uma instância do SoftwareSerial
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  // Inicialize a comunicação serial para depuração
  Serial.begin(115200);
  // Inicialize a comunicação serial com o módulo GPS
  ss.begin(GPSBaud);

  Serial.println(F("Iniciando..."));
}

void loop() {
  // Tente ler dados do GPS
  while (ss.available() > 0) {
    char c = ss.read();
    // Serial.write(c); // Imprime os dados brutos do GPS para depuração
    gps.encode(c);
  }

  
  // Se houver uma nova localização disponível, imprima os dados
  if (gps.location.isUpdated()) {
    Serial.print(F("Latitude: "));
    Serial.println(gps.location.lat(), 6);
    Serial.print(F("Longitude: "));
    Serial.println(gps.location.lng(), 6);
    Serial.print(F("Altitude: "));
    Serial.println(gps.altitude.meters());
    Serial.print(F("Satélites: "));
    Serial.println(gps.satellites.value());
    Serial.print(F("Precisão: "));
    Serial.println(gps.hdop.value());
    Serial.println();
  }


}
