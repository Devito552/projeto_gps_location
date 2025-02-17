#include <MPU9250_WE.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Definições do MPU9250
#define MPU9250_ADDR 0x68
MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR);

// Definições do GPS
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  ss.begin(GPSBaud);

  while (!Serial) {}  // Aguarda a inicialização da Serial
  Serial.println(F("Iniciando..."));

  Serial.println("MPU9250 conectado!");
  myMPU9250.autoOffsets();
  myMPU9250.enableGyrDLPF();
  myMPU9250.setGyrDLPF(MPU9250_DLPF_6);
  myMPU9250.setSampleRateDivider(5);
  myMPU9250.setGyrRange(MPU9250_GYRO_RANGE_250);
  myMPU9250.setAccRange(MPU9250_ACC_RANGE_2G);
  myMPU9250.enableAccDLPF(true);
  myMPU9250.setAccDLPF(MPU9250_DLPF_6);
}

void loop() {
  // Leitura do MPU9250
  xyzFloat gValue = myMPU9250.getGValues();
  xyzFloat gyr = myMPU9250.getGyrValues();
  xyzFloat magValue = myMPU9250.getMagValues();
  float temp = myMPU9250.getTemperature();

  Serial.println("--- MPU9250 Data ---");
  Serial.print("Aceleração (g) - x: ");
  Serial.print(gValue.x);
  Serial.print(", y: ");
  Serial.print(gValue.y);
  Serial.print(", z: ");
  Serial.println(gValue.z);

  Serial.print("Giroscópio (graus/s) - x: ");
  Serial.print(gyr.x);
  Serial.print(", y: ");
  Serial.print(gyr.y);
  Serial.print(", z: ");
  Serial.println(gyr.z);

  Serial.print("Campo Magnético (µT) - x: ");
  Serial.print(magValue.x);
  Serial.print(", y: ");
  Serial.print(magValue.y);
  Serial.print(", z: ");
  Serial.println(magValue.z);

  Serial.print("Temperatura (°C): ");
  Serial.println(temp);
  Serial.println();

  // Leitura do GPS
  while (ss.available() > 0) {
    char c = ss.read();
    gps.encode(c);
  }


  Serial.println("--- GPS Data ---");
  Serial.print("Latitude: ");
  Serial.println(gps.location.lat(), 6);
  Serial.print("Longitude: ");
  Serial.println(gps.location.lng(), 6);
  Serial.print("Altitude: ");
  Serial.println(gps.altitude.meters());
  Serial.print("Satélites: ");
  Serial.println(gps.satellites.value());
  Serial.print("Precisão: ");
  Serial.println(gps.hdop.value());
  Serial.println();

  delay(1000);
}
