void setup() {
  pinMode(22, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool valor = digitalRead(22);
  if(valor == false){
    Serial.println("branco");
  } else {
    Serial.println("preto");
}}