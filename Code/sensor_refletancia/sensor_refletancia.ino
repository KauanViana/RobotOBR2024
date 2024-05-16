#define digital_output 22

void setup() {
  pinMode(digital_output, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool valor = digitalRead(digital_output);
  if(valor == false){
    Serial.println("branco");
  } else {
    Serial.println("preto");
}}