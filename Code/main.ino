enum Direcao {FRENTE, ESQUERDA, DIREITA};

// Declarando as funções criadas
void setar_velocidade(int velocidade);
void mudar_direcao(Direcao index);

// Definindo em qual pino cada sensor de refletância está conectado
#define sensor_seguir_linha1 26 // O sensor de seguir linha 01 está conectado no pino 26
#define sensor_seguir_linha2 27 // O sensor de seguir linha 02 está conectado no pino 27
#define sensor_seguir_linha3 24 // O sensor de seguir linha 03 está conectado no pino 24
#define sensor_seguir_linha4 25 // O sensor de seguir linha 04 está conectado no pino 25

// Definindo os valores da leitura do sensor de refletância
#define BRANCO false // BRANCO equivale a false
#define PRETO true // PRETO equivale a true

int vel_motor; // A variável que guardará o valor da velocidade dos motores

void setup() {

  // Pinos que serão conectados nas ponte h
    pinMode(53,OUTPUT);
    pinMode(52,OUTPUT);
    pinMode(51,OUTPUT);
    pinMode(50,OUTPUT);

  // Pinos dos sensores de seguir linha
    pinMode(sensor_seguir_linha1,INPUT);
    pinMode(sensor_seguir_linha2,INPUT);
    pinMode(sensor_seguir_linha3,INPUT);
    pinMode(sensor_seguir_linha4,INPUT);

  // Pinos para velocidade dos motores
    pinMode(6,OUTPUT); //esse pino irá definir a velocidade do motor 01
    pinMode(5,OUTPUT); //esse pino irá definir a velocidade do motor 02

  // Setando velocidade inicial dos motores como 90
  vel_motor = 110;
}

void loop() {

  // P = Periferico | C = Central | E = Esquerdo | D = Direito
  bool sensor_CE = digitalRead(sensor_seguir_linha1); // Aqui, estamos pegando o que o sensor_CE está lendo e guardando em uma variável
  bool sensor_CD = digitalRead(sensor_seguir_linha2); // Aqui, estamos pegando o que o sensor_CD está lendo e guardando em uma variável
  bool sensor_PD = digitalRead(sensor_seguir_linha3); // Aqui, estamos pegando o que o sensor_PD está lendo e guardando em uma variável
  bool sensor_PE = digitalRead(sensor_seguir_linha4); // Aqui, estamos pegando o que o sensor_PE está lendo e guardando em uma variável

  // Se o sensor 01 ler PRETO o robo deve girar para ESQUERDA
  if(sensor_CE == PRETO && sensor_CD == BRANCO && sensor_PD == BRANCO && sensor_PE == BRANCO) { 
    setar_velocidade(vel_motor);
    mudar_direcao(ESQUERDA);

    delay(200);
  }

  // Se o sensor 02 ler PRETO o robo deve girar para DIREITA
  if(sensor_CD == PRETO && sensor_CE == BRANCO && sensor_PD == BRANCO && sensor_PE == BRANCO) { 
    setar_velocidade(vel_motor);
    mudar_direcao(DIREITA);

    delay(200);
  }

  // Se o sensor 03 ler PRETO o robo deve girar para DIREITA
  if(sensor_PD == PRETO && sensor_CD == BRANCO && sensor_CE == BRANCO && sensor_PE == BRANCO) { 
    setar_velocidade(vel_motor + 10);
    mudar_direcao(DIREITA);    

    delay(270);
  }

  // Se o sensor 04 ler PRETO o robo deve girar para ESQUERDA
  if(sensor_PE == PRETO && sensor_CD == BRANCO && sensor_PD == BRANCO && sensor_CE == BRANCO) {
    setar_velocidade(vel_motor + 10);
    mudar_direcao(ESQUERDA);

    delay(270);
  }

  // Se os sensores 02 e 01 lerem BRANCO o robo deve ir para FRENTE
  if(sensor_CE == BRANCO && sensor_CD == BRANCO && sensor_PD == BRANCO && sensor_PE == BRANCO) {
    setar_velocidade(vel_motor - 10);
    mudar_direcao(FRENTE);
  }

/*
  // Se todos os sensores lerem preto o robo deve parar
  if(sensor_CD == PRETO && sensor_CE == PRETO && sensor_PE == PRETO && sensor_PD == PRETO) {
    //O código abaixo faz o robo PARAR
    digitalWrite(53,LOW);
    digitalWrite(52,LOW);

    digitalWrite(51,LOW);
    digitalWrite(50,LOW);
}
*/


}

void setar_velocidade(int velocidade){
/*

  Para seguir a linha corretamente o robo precisa esta em uma velocidade que seja perfeita para ele percorrer o circuito
  O robo não deve andar muito rápido!!!

  para isso, temos que definir a velocidade que o robo deve andar

  no Arduino, o intervalo de velocidade está entre: 
    - 0(robo parado)
    - 255(velocidade máxima)
  Este código esta programado para o robo andar em uma velocidade de 110 

*/
//________________________________________________________________________________________________________________________________________
//  OBS: a velocidade dos motores não devem ser diferentes, ou seja, se um é 200 o outro também deverá ser 200
//________________________________________________________________________________________________________________________________________

  analogWrite(6,velocidade);// a velocidade do motor 01 é 110
  analogWrite(5,velocidade);// a velocidade do motor 02 é 110
}

void mudar_direcao(Direcao index){
  switch(index){
    case FRENTE:
      // Faz o robô andar pra frente
      digitalWrite(53,LOW);
      digitalWrite(52,HIGH);

      digitalWrite(51,HIGH);
      digitalWrite(50,LOW);
      break;

    case DIREITA:
      // Faz o robô girar para a direita
      digitalWrite(53,LOW);// motor 01
      digitalWrite(52,HIGH);// motor 01

      digitalWrite(51,LOW);// motor 02
      digitalWrite(50,HIGH);// motor 02
      break;

    case ESQUERDA:
      // Faz o robô girar para a esquerda
      digitalWrite(53,HIGH);// motor 01
      digitalWrite(52,LOW);// motor 01

      digitalWrite(51,HIGH);// motor 02
      digitalWrite(50,LOW);// motor 02
      break;
  }
}
