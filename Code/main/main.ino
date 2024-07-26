/* Comentário de Pedro pra nossa equipe:

 O código abaixo foi feito com um Arduino Uno, porém o ideal é ser passado para um arduino mega
 Esse código inicial serve de base para que voces continuem desenvolvendo ele
 O que vcs podem fazer:
 1 - melhorar a estrutura do robo para tudo ficar bem posicionado, inclusive os fios
 2 - aprimorar o código do robo, para ajustar a velocidade, leitura da linha, programação e etc...
 3 - adicionar +2 sensores para o robo ser capaz de percorrer os caminhos em 90 graus
 assim que isso tiver feito, vcs podem comecar a investir no proximo passo...
*/

#define sensor_seguir_linha1 12 // O sensor de seguir linha 01 está conectado no pino 12
#define sensor_seguir_linha2 13 // O sensor de seguir linha 02 está conectado no pino 13

#define motor_01 6 // O motor 01 está conectado no pino 06
#define motor_02 5 // O motor 02 está conectado no pino 05

#include <Wire.h> // Biblioteca para se comunicar com o giroscópio
#include <MPU6050.h> // Biblioteca para lidar com o giroscópio

MPU6050 mpu; // Objeto da biblioteca MPU6050.h para interagir com o sensor do giroscópio

int16_t gx, gy, gz; // Variáveis para armazenar os valores brutos das taxas de rotação em torno dos eixos X, Y e Z
float angulo_X = 0.0;  // Variável para armazenar o ângulo X em graus
float angulo_Y = 0.0;  // Variável para armazenar o ângulo Y em graus
float angulo_Z = 0.0;  // Variável para armazenar o ângulo Z em graus

unsigned long tempo_ultima_leitura; // Variável que armazenará o tempo da última leitura
float intervalo_tempo; // Variável para armazenar o intervalo de tempo entre duas leituras.

void setup() {
    // Pinos que serão conectados na ponte h
    pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
    //_______________
    //Pinos dos sensores de seguir linha
    pinMode(sensor_seguir_linha1,INPUT);
    pinMode(sensor_seguir_linha2,INPUT);
    //_______________
    //Pinos para velocidade dos motores
    pinMode(motor_01,OUTPUT); //esse pino irá definir a velocidade do motor 01
    pinMode(motor_02,OUTPUT); //esse pino irá definir a velocidade do motor 02

    // Inicializando o Serial Monitor e o MPU6050 (Giroscópio)
    Wire.begin();
    Serial.begin(9600);
    mpu.initialize();

    // Conectando com o MPU6050 (Giroscópio)
    if (mpu.testConnection()) {
        Serial.println("MPU6050 conectado com sucesso");
    } else {
        Serial.println("Erro ao conectar ao MPU6050");
    }

    tempo_ultima_leitura = millis();
}


void loop() {
/*
    O giroscópio do MPU6050 funciona medindo a taxa de rotação (velocidade angular) em torno dos três eixos: X, Y e Z. 
    Essas medições são feitas utilizando o efeito Coriolis, que é a detecção da força resultante do movimento 
    do sensor em relação ao eixo de rotação. Os valores lidos 
    são em unidades brutas (raw values). Isso significa que são números inteiros que representam a taxa de 
    rotação sem qualquer conversão ou ajuste. Para obter o ângulo de rotação acumulado ao longo do tempo, 
    é necessário somar continuamente a pequena quantidade de rotação ocorrida durante pequenos intervalos de tempo.

    A fórmula básica para calcular o ângulo acumulado a partir da taxa de rotação é: ângulo = taxa de rotação * tempo

    // Calculando o intervalo de tempo
    OBS: A função millis() retorna um valor numérico do tipo "unsigned long", referente a quanto tempo em milissegundos 
    passou desde que o Arduino começou a executar o programa até o momento em que a função foi chamada. Esse valor é
    passado para a variável que ela foi atribuída
*/
    unsigned long tempo_atual = millis();
    intervalo_tempo = (tempo_atual - tempo_ultima_leitura) / 1000.0;  // O "/ 1000.0" para converter para segundos
    tempo_ultima_leitura = tempo_atual;

    // Lendo as taxas de rotação (em raw values)
    mpu.getRotation(&gx, &gy, &gz);

    // Convertendo os valores para graus por segundo (ajuste o fator de conversão conforme o alcance configurado)
    float taxa_rotacao_X = gx / 65.5;
    float taxa_rotacao_Y = gy / 65.5;
    float taxa_rotacao_Z = gz / 65.5

    // Integrando as taxas de rotação e o intervalo de tempo para obter o ângulo
    angulo_X += taxa_rotacao_X * intervalo_tempo;
    angulo_Y += taxa_rotacao_Y * intervalo_tempo;
    angulo_Z += taxa_rotacao_Z * intervalo_tempo;

    // Exibe os ângulos calculados
    Serial.print("Ângulo X: "); Serial.print(angulo_X); Serial.print("\t");
    Serial.print("Ângulo Y: "); Serial.print(angulo_Y); Serial.print("\t");
    Serial.print("Ângulo Z: "); Serial.println(angulo_Z);

    delay(1000);

/*
    Para saber se o sensor de seguir linha está lendo branco ou preto temos que guardar a sua leitura
    em uma variável do tipo "bool"
    Se o sensor de seguir linha 01 ler PRETO a variável "sensor_01" será igual a "true"
    Se o sensor de seguir linha 01 ler BRANCO a variável "sensor_01" será igual a "false"
    A partir das variáveis "sensor_01" e "sensor_02" podemos mudar a rotação do robo
*/
    bool sensor_01 = digitalRead(sensor_seguir_linha1); // Variável que recebe a leitura do sensor_01
    bool sensor_02 = digitalRead(sensor_seguir_linha2); // Variável que recebe a leitura do sensor_02

/*
    Para seguir a linha corretamente o robo precisa estar em uma velocidade que seja perfeita para ele
    percorrer o circuito. O robo não deve andar muito rápido!!! Para isso, é preciso definir a 
    velocidade que o robo deve andar no Arduino, o intervalo de velocidade está entre:

    - 0 (robo parado)
    - 255 (velocidade máxima)

    Este código esta programado para o robo andar em uma velocidade de 110

    OBS: a velocidade dos motores não devem ser diferentes, ou seja, se um é 200 o outro também deverá
    ser 200
*/
    analogWrite(motor_01, 110); // a velocidade do motor 01 é 110
    analogWrite(motor_02, 110); // a velocidade do motor 02 é 110

    if(sensor_01 == true) { // Se o sensor 01 ler PRETO o robo deve girar para ESQUERDA
    // O código abaixo faz o robo girar para ESQUERDA
        digitalWrite(2,HIGH);// motor 01
        digitalWrite(4,LOW);// motor 01
        digitalWrite(7,HIGH);// motor 02
        digitalWrite(8,LOW);// motor 02
    }

    if(sensor_02 == true) { // Se o sensor 02 ler PRETO o robo deve girar para DIREITA
        //O código abaixo faz o robo girar para DIREITA
        digitalWrite(2,LOW);// motor 01
        digitalWrite(4,HIGH);// motor 01
        digitalWrite(7,LOW);// motor 02
        digitalWrite(8,HIGH);// motor 02
    }

    if(sensor_02 == false && sensor_01 == false) { // Se os dois sensores lerem branco o robo deve ir para frente
        // O código abaixo faz o robo ANDAR PARA FRENTE
        digitalWrite(2,LOW);
        digitalWrite(4,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(8,LOW);
    }

    if(sensor_02 == true && sensor_01 == true) { // Se os dois sensores lerem preto o robo deve parar
        // O código abaixo faz o robo PARAR
        digitalWrite(2,LOW);
        digitalWrite(4,LOW);
        digitalWrite(7,LOW);
        digitalWrite(8,LOW);
    }
}