#include <L298N.h>  // Biblioteca ponte H

//Constantes
const int quantia_de_sensores_de_refletancia = 5;
const int tamanho_lista = 32;
const int quantia_de_motores = 2;

bool preto = true;
bool branco = false;

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

//Sensores de refletância
#define direita_2 4
#define direita_1 3
#define meio 2
#define esquerda_1 1
#define esquerda_2 0

const int pinos_sensores_refletancia[] = { esquerda_2, esquerda_1, meio, direita_1, direita_2 };

//níveis de força para os motores
const int n1 = 0;
const int n2 = 40;
const int n3 = 80;
const int n4 = 120;
const int n5 = 160;

// Matriz de forças de motor
int niveis_forca_motor[tamanho_lista][quantia_de_motores] = {
  { n3, n3 }, { n5, n1 }, { n4, n2 }, { n4, n3 },
  { n3, n3 }, { n3, n2 }, { n4, n3 }, { n5, n1 },
  { n2, n4 }, { n3, n2 }, { n2, n2 }, { n3, n1 },
  { n3, n4 }, { n2, n3 }, { n2, n2 }, { n5, n1 },
  { n1, n5 }, { n2, n2 }, { n2, n3 }, { n3, n2 },
  { n2, n3 }, { n2, n2 }, { n3, n2 }, { n5, n1 },
  { n3, n4 }, { n2, n3 }, { n2, n3 }, { n3, n3 },
  { n1, n5 }, { n1, n5 }, { n1, n5 }, { n3, n3 }
};

//Inverta em caso de inversão
#define esquerda_frente motor_esquerda.backward
#define esquerda_tras motor_esquerda.forward

#define direita_frente motor_direita.backward
#define direita_tras motor_direita.forward

int valores_anteriores_sensor_refletancia[] = { 0, 0, 0, 0, 0 };
int valores_atuais_sensor_refletancia[] = { 0, 0, 0, 0, 0 };

// Cores atuais do sensor de refletância
bool cor_atual[quantia_de_sensores_de_refletancia] = { branco, branco, branco, branco, branco };

int delta_para_mudar = 30;

void ler_sensores_refletancia_robo() {
  //Salva o valor, antes dele mudar, no valor anterior
  for (int i = 0; i < quantia_de_sensores_de_refletancia; i++) {
    valores_anteriores_sensor_refletancia[i] = valores_atuais_sensor_refletancia[i];
  }

  //Lê o valor de cada sensor de refletância
  for (int i = 0; i < quantia_de_sensores_de_refletancia; i++) {
    valores_atuais_sensor_refletancia[i] = analogRead(pinos_sensores_refletancia[i]);
  }
}

void comparar_valores_de_sensores() {
  for (int i = 0; i < quantia_de_sensores_de_refletancia; i++) {
    int delta = valores_atuais_sensor_refletancia[i] - valores_anteriores_sensor_refletancia[i];
    int delta_abs = abs(delta);

    if (delta_abs > delta_para_mudar) {
      if (delta < 0 && cor_atual[i] == preto) {
        cor_atual[i] = branco;
      } else if (delta > 0 && cor_atual[i] == branco) {
        cor_atual[i] = preto;
      }
    }
  }
}

//Converte a leitura do sensor de refletância em um número de 5 bits
int sensores_refletancia_para_numero() {
  //Converte a lista de estados em um número de 5 bits
  int numero_resultado = 0;
  for (int i = 0; i < quantia_de_sensores_de_refletancia; i++) {
    numero_resultado |= (cor_atual[i] << i);
  }

  return numero_resultado;
}

void setup() {
  //definindo pinos dos sensores de refletância
  for (int i = 0; i < quantia_de_sensores_de_refletancia; i++) {
    pinMode(pinos_sensores_refletancia[i], INPUT);
  }

  Serial.begin(9600);
  while (!Serial) {
    //fazer nada até serial carregar
  }

  delay(2000);
  ler_sensores_refletancia_robo();
  ler_sensores_refletancia_robo();
}

void loop() {
  ler_sensores_refletancia_robo();
  comparar_valores_de_sensores();

  motor_esquerda.setSpeed(niveis_forca_motor[sensores_refletancia_para_numero()][0]);
  motor_direita.setSpeed(niveis_forca_motor[sensores_refletancia_para_numero()][1]);

  Serial.print("Número: ");
  Serial.print(sensores_refletancia_para_numero());
  Serial.print(" (");
  Serial.print(niveis_forca_motor[sensores_refletancia_para_numero()][0]);
  Serial.print(", ");
  Serial.print(niveis_forca_motor[sensores_refletancia_para_numero()][1]);
  Serial.println(")");

  esquerda_frente();
  direita_frente();
  delay(10);
}