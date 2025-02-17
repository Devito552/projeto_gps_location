#include <MPU9250_WE.h>
#include <Wire.h>

#define MPU9250_ADDR 0x68

MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR);

void setup() {
  Serial.begin(115200);
  Wire.begin();  // Usa os pinos I2C padrão (A4 para SDA, A5 para SCL no Arduino Uno)
  
  while(!Serial) {}
  
  if(!myMPU9250.init()){
    Serial.println("MPU9250 não conectado!");
  }
  else{
    Serial.println("MPU9250 está conectado");
  }

  // Configurar MPU9250
  myMPU9250.autoOffsets();
  myMPU9250.enableGyrDLPF();
  myMPU9250.setGyrDLPF(MPU9250_DLPF_6);
  myMPU9250.setSampleRateDivider(5);
  myMPU9250.setGyrRange(MPU9250_GYRO_RANGE_250);
  myMPU9250.setAccRange(MPU9250_ACC_RANGE_2G);
  myMPU9250.enableAccDLPF(true);
  myMPU9250.setAccDLPF(MPU9250_DLPF_6);
  
  Serial.println("Iniciando leitura do MPU9250...");
}

void loop() {
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
  delay(1000);
}
