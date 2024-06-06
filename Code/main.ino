#include <L298N.h>  // Biblioteca ponte H

//Constantes
const int quantia_de_sensores_de_refletancia = 5;
const int tamanho_lista = 32;
const int quantia_de_motores = 2;
const int forca_maxima_motor = 120;

bool preto = true;
bool branco = false;

//pino botão
#define botao 49

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

//Inverta em caso de inversão
#define esquerda_frente motor_esquerda.backward
#define esquerda_tras motor_esquerda.forward

#define direita_frente motor_direita.backward
#define direita_tras motor_direita.forward

int valores_anteriores_sensor_refletancia[] = { 0, 0, 0, 0, 0 };
int valores_atuais_sensor_refletancia[] = { 0, 0, 0, 0, 0 };

// Cores atuais do sensor de refletância
bool cor_atual[quantia_de_sensores_de_refletancia] = { branco, branco, branco, branco, branco };


void ler_sensores_refletancia_robo() {
  for (int i = 0; i < quantia_de_sensores_de_refletancia; i++) {
    valores_anteriores_sensor_refletancia[i] = valores_atuais_sensor_refletancia[i]; //Salva o valor, antes dele mudar, no valor anterior
    valores_atuais_sensor_refletancia[i] = analogRead(pinos_sensores_refletancia[i]); //Lê o valor de cada sensor de refletância
  }
}

int delta_para_mudar = 30;

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

int calcular_erro(int leitura) {
    int erro = 0;
  
    switch (leitura) {
        case 1:
            erro = 2;
            break;
        case 3:
            erro = 1.75;
            break;
        case 2:
            erro = 1.50;
            break;
        case 6:
            erro = 1;
            break;
        case 4:
            erro = 0;
        case 12:
            erro = -1;
            break;
        case 8:
            erro = -1.50;
            break;
        case 24:
            erro = -1.75;
            break;
        case 16:
            erro = -2;
            break;
        default:
            break;
    }
    return erro;
}

int P = 0;
int I = 0;
int D = 0;
int PID = 0;

int Kp = 15;
int Ki = 0;
int Kd = 15;

int erro_anterior = 0;

void calcula_pid(){
  int binario_leitura = sensores_refletancia_para_numero();
  int erro = calcular_erro(binario_leitura);
  int I_maximo = forca_maxima_motor;

  if (erro == 0){
    I = 0;
  }

  P = erro;
  I += erro;

  if(I > I_maximo){
    I = I_maximo;
  }else if(I < -I_maximo){
    I = -I_maximo;
  }

  D = erro - erro_anterior;
  PID = (Kp*P) + (Ki*I) + (Kd*D);
  erro_anterior = erro;
}


void controle_motor(){
  bool indo_para_a_esquerda = PID > 0; // True se o robô estiver indo para a esquerda

  int forca_esquerda = 0;
  int forca_direita = 0;

  if (indo_para_a_esquerda){
    //indo para a esquerda
    forca_direita = forca_maxima_motor - PID;
    forca_esquerda = forca_maxima_motor;
  }else{
    //indo para a direita
    forca_esquerda = forca_maxima_motor - PID;
    forca_direita = forca_maxima_motor;
  }

  Serial.prinln(forca_esquerda);
  Serial.prinln(forca_direita);

  motor_esquerda.setSpeed(forca_esquerda);
  motor_direita.setSpeed(forca_direita);

  esquerda_frente();
  direita_frente();
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

  pinMode(botao, INPUT);

  delay(2000);
  ler_sensores_refletancia_robo();
  ler_sensores_refletancia_robo();
}

void loop() {
  ler_sensores_refletancia_robo();
  comparar_valores_de_sensores();

  calcula_pid();
  controle_motor();

  Serial.println(PID);

  delay(10);
}