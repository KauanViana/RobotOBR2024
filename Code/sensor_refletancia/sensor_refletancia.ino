#define direita_1 22
#define direita_2 23
#define centro 24
#define esquerda_1 25
#define esquerda_2 26

void setup() {
  pinMode(direita_1, INPUT);
  pinMode(direita_2, INPUT);
  pinMode(centro, INPUT);
  pinMode(esquerda_1, INPUT);
  pinMode(esquerda_2, INPUT);
  Serial.begin(9600);
}

String sensorAcionado() {
    bool sensor_dir1 = digitalRead(direita_1);
    bool sensor_dir2 = digitalRead(direita_2);
    bool sensor_centro = digitalRead(centro);
    bool sensor_esq1 = digitalRead(esquerda_1);
    bool sensor_esq2 = digitalRead(esquerda_2);

    bool sensores[] = {sensor_dir1, sensor_dir2, sensor_centro, sensor_esq1, sensor_esq2};
    String sensor_nome[] = {"sensor_dir1", "sensor_dir2", "sensor_centro", "sensor_esq1", "sensor_esq2"};

    for (int i = 0; i < 5; i++) {
        if (sensores[i]) {
            return sensor_nome[i];
        }
    }
    return "Nenhum sensor foi acionado!";
}

void loop() {
  String sensor_acionado = sensorAcionado();
  Serial.println(sensor_acionado);
  delay(1000);
}
