#include <HCSR04.h>



UltraSonicDistanceSensor distanceSensor( 22,23 );

void setup() {

  Serial.begin(9600);

}

void loop() {

  float distancia = distanceSensor.measureDistanceCm();

Serial.println(distancia);
delay(1000);

}