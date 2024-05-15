#include <TCS3200.h>

#define S0_PIN 22
#define S1_PIN 23
#define S2_PIN 26
#define S3_PIN 27
#define OUT_PIN 52

TCS3200 colorSensor(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);

void setup() {
colorSensor.begin();
/*pinMode(22,INPUT);//s0
pinMode(23,INPUT);//s1
pinMode(24,INPUT);//oe
pinMode(26,INPUT);//s2
pinMode(27,INPUT);//s3*/
Serial.begin(9600);
Serial.println("Inicializado");
}

void loop() {
  // Read color intensity values for individual color channels
  uint8_t redIntensity = colorSensor.read_red();
  uint8_t greenIntensity = colorSensor.read_green();
  uint8_t blueIntensity = colorSensor.read_blue();
  uint8_t clearIntensity = colorSensor.read_clear();

Serial.print("R: ");
Serial.print(redIntensity);
Serial.print(" G: ");
Serial.print(greenIntensity);
Serial.print(" B: ");
Serial.println(blueIntensity);
  delay(1000);
}
