//Programação Infinity + Colégio Militar
//Seguidor De Linha Simples 2 Sensores
//16/09/2022

#include <AFMotor.h> 


//  Definição Do Sharp IR
int sensorValue = 0;
int cmValue = 0;

//Pino do sensor sharp
#define sharp_sensor A15

// Definir as variaveis para o calculo do SHARP
float volts = analogRead(sharp_sensor) * 0.0048828125;
int sharp_distance = 26 * pow(volts, -1);

//  Declaração do motores
AF_DCMotor motorD(1); //Motor Direito
AF_DCMotor motorE(3); //Motor Esquerdo

//  Pinos do seguidor de linha
#define pin_sensor1 22 // Esquerda
#define pin_sensor2 24 // Meio Esquerda
#define pin_sensor3 26 // Meio
#define pin_sensor4 28 // Meio Direita
#define pin_sensor5 30 // Direita
#define pin_CLP = 32 // CLP
#define pin_near = 36 // Near

//  Definir Todos os sensores IR como 0
bool sensor1, sensor2, sensor3, sensor4, sensor5 = 0;

// Definindo funçoes

void forcamotor (int vel_E, int vel_D) {  // *Velocidades dos motores*
  if (vel_E >= 0) {
    motorE.run(FORWARD);
    motorE.setSpeed(vel_E);
  }
  else {
    motorE.run(BACKWARD);
    motorE.setSpeed(abs(vel_E));
  }

  if (vel_D >= 0) {
    motorD.run(FORWARD);
    motorD.setSpeed(vel_D);
  }
  else {
    motorD.run(BACKWARD);
    motorD.setSpeed(abs(vel_D));
  }
}

void seguidorlinha () { //  *Condicional do seguidor de linha*
  if (sensor2 == HIGH && sensor3 == HIGH) {    // sensor 3 e sensor 2 no preto SIGA
    forcamotor(180, 150);
  }

  else if (sensor2 == LOW && sensor3 == LOW) {  // sensor 3 e sensor 2 no branco SIGA
    forcamotor(180, 150);
  }

  else if (sensor2 == LOW && sensor3 == HIGH) {  // Virar para a DIREITA
    forcamotor (-150, 180);
  }

  else if (sensor2 == HIGH && sensor3 == LOW) {  //Virar para a esquerda
    forcamotor (180, -150);
    } 
}

void seguidorImbroxavel () {

  bool e2a = sensor1 == HIGH;
  bool e1a = sensor2 == HIGH;
  bool mea = sensor3 == HIGH;
  bool d1a = sensor4 == HIGH;
  bool d2a = sensor5 == HIGH;

  bool e2i = sensor1 == LOW;
  bool e1i = sensor2 == LOW;
  bool mei = sensor3 == LOW;
  bool d1i = sensor4 == LOW;
  bool d2i = sensor5 == LOW;

  bool frente1 = e2i && e1i && mea && d1i && d2i; // 0 0 1 0 0
  bool frente2 = e2i && e1i && mei && d1i && d2i; // 0 0 0 0 0
  bool frente3 = e2a && e1a && mea && d1a && d2a; // 1 1 1 1 1
  bool frente4 = e2i && e1a && mea && d1a && d2i; // 0 1 1 1 0
  bool frente5 = e2a && e1i && mea && d1i && d2a; // 1 0 1 0 1
  bool frente6 = e2a && e1i && mea && d1i && d2a; // 1 1 0 1 1
  bool frente7 = e2i && e1a && mei && d1a && d2i; // 0 1 0 1 0
  bool frente8 = e2a && e1i && mei && d1i && d2a; // 1 0 0 0 1

  bool esquerda1 = e2a && e1a && mea && d1i && d2i; // 1 1 1 0 0
  bool esquerda2 = e2a && e1a && mei && d1i && d2i; // 1 1 0 0 0
  bool esquerda3 = e2a && e1i && mea && d1i && d2i; // 1 0 1 0 0
  bool esquerda4 = e2a && e1i && mei && d1i && d2i; // 1 0 0 0 0
  bool esquerda5 = e2i && e1a && mea && d1i && d2i; // 0 1 1 0 0
  bool esquerda6 = e2i && e1a && mei && d1i && d2i; // 0 1 0 0 0

  bool direita1 = e2i && e1i && mea && d1a && d2a; // 0 0 1 1 1
  bool direita2 = e2i && e1i && mei && d1a && d2a; // 0 0 0 1 1
  bool direita3 = e2i && e1i && mea && d1i && d2a; // 0 0 1 0 1
  bool direita4 = e2i && e1i && mei && d1i && d2a; // 0 0 0 0 1
  bool direita5 = e2i && e1i && mea && d1a && d2i; // 0 0 1 1 0
  bool direita6 = e2i && e1i && mei && d1a && d2i; // 0 0 0 1 0

  if (frente1 || frente2 || frente3 || frente4 || frente5 || frente6 || frente7 || frente8) {

    forcamotor(180, 180); //mudar valores para mudar velocidade dos motores, ajustar e td mais
    Serial.println("Frente");
    
    }

  if (esquerda1 || esquerda2 || esquerda3 || esquerda4 || esquerda5 || esquerda6) {

    forcamotor(180, -180); //mudar valores para mudar velocidade dos motores, ajustar e td mais
    Serial.println("Esquerda");
    
    }

  if (direita1 || direita2 || direita3 || direita4 || direita5|| direita6) { 
    
    forcamotor(-180, 180); //mudar valores para mudar velocidade dos motores, ajustar e td mais
    Serial.println("Direita");
    }
  

}


void setup() {
  //  *Sensor seguidor de linha*
  pinMode(pin_sensor1, INPUT); // Branco = LOW; PRETO = HIGH
  pinMode(pin_sensor2, INPUT);
  pinMode(pin_sensor3, INPUT); // Branco = LOW; PRETO = HIGH
  pinMode(pin_sensor4, INPUT);
  pinMode(pin_sensor5, INPUT); // Branco = LOW; PRETO = HIGH
  
  //  *Declaração Dos Leds*
  pinMode (32, OUTPUT); //Led esquerdo
  pinMode (34, OUTPUT); //Led direito

  //  *Declaração do Sharp IR*
  pinMode(sharp_sensor, INPUT);

  Serial.begin(9600);
  
}
  

void loop() {
  //  *Condicional Obstáculo*
  volts = analogRead(sharp_sensor) * 0.0048828125;
  sharp_distance = 26 * pow(volts, -1);

  if (sharp_distance <= 7) {
    //Fazer Programação De Desvio De Obstáculo
  }

  //  *Seguidor De Linha*
  //  *Leitura dos Sensores*
  sensor2 = digitalRead(pin_sensor2); //Meio direita
  sensor3 = digitalRead(pin_sensor3); //Meio esquerda

  //  *Condicional Seguidor De Linha*
  seguidorlinha ();
}
