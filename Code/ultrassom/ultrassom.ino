#include <HCSR04.h>

//Todo definir qual pino é echo e qual é trigger

UltraSonicDistanceSensor distanceSensor( 22,23 );

void setup() {

  Serial.begin(9600);

}

void loop() {

  float distancia = distanceSensor.measureDistanceCm();

Serial.println(distancia);
delay(1000);

}