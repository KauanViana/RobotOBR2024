//código motores com ponte H

#define ein1 53 //esquerda in 1
#define ein2 52 //esquerda in 2
#define din3 51 //direita in 1
#define din4 50 //direita in 2

void setup() {
  pinMode(ein1, OUTPUT);
  pinMode(ein2, OUTPUT);
  pinMode(din3, OUTPUT);
  pinMode(din4, OUTPUT);
  Serial.begin(9600);
  Serial.println("Inicializado!");
  delay(5000);
}

void loop() {
  digitalWrite(ein1, HIGH);
  digitalWrite(ein2, LOW);
  digitalWrite(din3, HIGH);
  digitalWrite(din4, LOW);
  delay(1000);
}