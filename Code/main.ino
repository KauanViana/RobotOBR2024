#include <L298N.h>  // Biblioteca ponte H

//Motor da direita

#define IN1 50
#define IN2 51
#define ENA 3
L298N motor_direita(ENA, IN1, IN2);

//Motor da esquerda

#define IN3 52
#define IN4 53
#define ENB 4
L298N motor_esquerda(ENB, IN3, IN4);

//refletância

#define do_direita_2 22
#define do_direita_1 23
#define do_meio 24
#define do_esquerda_1 25
#define do_esquerda_2 26

const int inputPins[] = {do_esquerda_2, do_esquerda_1, do_meio, do_direita_1, do_direita_2}; // Pins for the digital inputs
int inputValue[5]; // Array to store the input values

const int tamanho_lista = 32; // Define the size of the list

// Create an array of NumberPair structures
int possibilidades_motor[tamanho_lista][2] = {
{255,255},{255,255},{255,255},{255,255},
{255,255},{255,255},{255,255},{255,255},
{255,255},{255,255},{255,255},{255,255},
{255,255},{255,255},{255,255},{255,255},
{255,255},{255,255},{255,255},{255,255},
{255,255},{255,255},{255,255},{255,255},
{255,255},{255,255},{255,255},{255,255},
{255,255},{255,255},{255,255},{255,255}
};


//Inverta em caso de inversão
void esquerda_frente() {
  motor_esquerda.backward();
}
void esquerda_tras() {
  motor_esquerda.forward();
}

void direita_frente() {
  motor_direita.backward();
}
void direita_tras() {
  motor_direita.forward();
}

int sensor_array_to_number(){
  // Read the state of each input pin
  for (int i = 0; i < 5; i++) {
    inputValue[i] = digitalRead(inputPins[i]);
  }
  
  // Convert the binary input values to a single 5-bit number
  int number = 0;
  for (int i = 0; i < 5; i++) {
    number |= (inputValue[i] << i);
  }

  // Print the result to serial monitor
  return number;
}

void setup() {
  //motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //refletância
  for (int i = 0; i < 5; i++) {
    pinMode(inputPins[i], INPUT); // Set input pins
  }

  Serial.begin(9600);
  while (!Serial) {
    //do nothing
  }
  motor_esquerda.setSpeed(128);
  motor_direita.setSpeed(128);
}

void loop() {
  esquerda_frente();
  direita_frente();
  // put your main code here, to run repeatedly:
  bool valor_direita_1 = digitalRead(do_direita_1);
  bool valor_direita_2 = digitalRead(do_direita_2);

  bool valor_esquerda_1 = digitalRead(do_esquerda_1);
  bool valor_esquerda_2 = digitalRead(do_esquerda_2);

  bool preto = true;
  bool branco = false;

  Serial.println(possibilidades_motor[sensor_array_to_number()][1]);

  if (valor_direita_1 == branco && valor_esquerda_1 == branco || valor_direita_1 == preto && valor_esquerda_1 == preto) {  // reto
    
    Serial.println("Andando frente");
  }
  if (valor_direita_1 == branco && valor_esquerda_1 == preto) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Curvando direita");
  }
  if (valor_direita_1 == preto && valor_esquerda_1 == branco) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("Curvando esquerda");
  }
  /*
  if (valor_direita_2 == branco && valor_esquerda_2 == preto){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(150);
    Serial.println("Curvando direita 1");
  }
  if (valor_direita_2 == preto && valor_esquerda_2 == branco){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(150);
    Serial.println("Curvando esquerda 1");
  }//*/
}