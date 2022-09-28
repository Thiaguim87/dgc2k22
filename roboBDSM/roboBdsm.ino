// Importando bibliotecas

#include <AFMotor.h> //Motores

// Declarando motores
AF_DCMotor motorD(1);
AF_DCMotor motorE(3);

// Seguidor de linha - sensores - * modelo *
#define pin_sensor1 22 // Esquerda
#define pin_sensor2 24 // Meio Esquerda
#define pin_sensor3 26 // Meio
#define pin_sensor4 28 // Meio Direita
#define pin_sensor5 30 // Direita
#define pin_CLP = 32 // CLP
#define pin_near = 36 // Near

bool e2, e1, me, d1, d2 = 0;

// Definindo condicionais do seguidor de linha COM MEIO ( 1 = preto && 0 = branco )
  
bool frente1 = e2 == LOW && e1 == LOW && me == HIGH && d1 == LOW && d2 == LOW;      // 0 0 1 0 0 -> me
bool frente2 = e2 == HIGH && e1 == HIGH && me == HIGH && d1 == HIGH && d2 == HIGH;  // 1 1 1 1 1 -> e2 e1 me d1 d2
bool frente3 = e2 == LOW && e1 == LOW && me == LOW && d1 == LOW && d2 == LOW;       // 0 0 0 0 0 -> NULL

bool direita1 = e2 == LOW && e1 == LOW && me == HIGH && d1 == HIGH && d2 == HIGH;   // 0 0 1 1 1 -> me d1 d2
bool direita2 = e2 == LOW && e1 == LOW && me == LOW && d1 == HIGH && d2 == HIGH;    // 0 0 0 1 1 -> d1 d2
bool direita3 = e2 == LOW && e1 == LOW && me == HIGH && d1 == HIGH && d2 == LOW;    // 0 0 1 1 0 -> me d1
bool direita4 = e2 == LOW && e1 == LOW && me == LOW && d1 == HIGH && d2 == LOW;     // 0 0 0 1 0 -> d1
bool direita5 = e2 == LOW && e1 == LOW && me == HIGH && d1 == LOW && d2 == HIGH;    // 0 0 1 0 1 -> me d2
bool direita6 = e2 == LOW && e1 == LOW && me == LOW && d1 == LOW && d2 == HIGH;     // 0 0 0 0 1 -> d2

bool esquerda1 = e2 == HIGH && e1 == HIGH && me == HIGH && d1 == LOW && d2 == LOW;   // 1 1 1 0 0 -> e2 e1 me
bool esquerda2 = e2 == HIGH && e1 == HIGH && me == LOW && d1 == LOW && d2 == LOW;    // 1 1 0 0 0 -> e2 e1
bool esquerda3 = e2 == LOW && e1 == HIGH && me == HIGH && d1 == LOW && d2 == LOW;    // 0 1 1 0 0 -> e1 me
bool esquerda4 = e2 == LOW && e1 == HIGH && me == LOW && d1 == LOW && d2 == LOW;     // 0 1 0 0 0 -> e1
bool esquerda5 = e2 == HIGH && e1 == LOW && me == HIGH && d1 == LOW && d2 == LOW;    // 1 0 1 0 0 -> e2 me
bool esquerda6 = e2 == HIGH && e1 == LOW && me == LOW && d1 == LOW && d2 == LOW;     // 1 0 0 0 0 -> e2

void seguidorBdsm () { //  *Condicional do seguidor de linha*

  // SEGUIR FRENTE
  
  if (frente1) {            // 0 0 1 0 0 -> siga frente
    forcamotor(180, 150);
  }

  else if (frente2) {       // 1 1 1 1 1 -> siga frente
    forcamotor(180, 150);
  }

  else if (frente3) {       // 0 0 0 0 0 -> siga frente
    forcamotor(180, 150);
  }

  // SEGUIR DIREITA

  else if (direita1) {      // 0 0 1 1 1 -> virar direita
    forcamotor (-150, 180);
  }

  else if (direita2) {      // 0 0 0 1 1 -> virar direita
    forcamotor (-150, 180);
    }

  else if (direita3) {      // 0 0 1 1 0 -> virar direita
    forcamotor (-150, 180);
  }

  else if (direita4) {      // 0 0 0 1 0 -> virar direita
    forcamotor (-150, 180);
    }

  else if (direita5) {      // 0 0 1 0 1 -> virar direita
    forcamotor (-150, 180);
  }

  else if (direita6) {      // 0 0 0 0 1 -> virar direita
    forcamotor (-150, 180);
    }

   // SEGUIR ESQUERDA

    
  else if (esquerda1) {     // 1 1 1 0 0 -> virar esquerda
    forcamotor (180, -150);
    
  }
  else if (esquerda2) {     // 1 1 0 0 0 -> virar esquerda
    forcamotor (180, -150);
    
  }

  else if (esquerda3) {     // 0 1 1 0 0 -> virar esquerda
    forcamotor (180, -150);
    
  }
  else if (esquerda4) {     // 0 1 0 0 0 -> virar esquerda
    forcamotor (180, -150);
    
  }

  else if (esquerda5) {     // 1 0 1 0 0 -> virar esquerda
    forcamotor (180, -150);
    
  }
  else if (esquerda6) {     // 1 0 0 0 0 -> virar esquerda
    forcamotor (180, -150);
    
  }

  
}


// Definindo a funçao dos motores

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

void setup() {
  // Seguidor de linha
  pinMode(pin_sensor1, INPUT); // BRANCO = LOW && PRETO = HIGH
  pinMode(pin_sensor2, INPUT);
  pinMode(pin_sensor3, INPUT);
  pinMode(pin_sensor4, INPUT);
  pinMode(pin_sensor5, INPUT);

  // Declaraçao dos Leds
  pinMode (32, OUTPUT); //Led esquerdo
  pinMode (34, OUTPUT); //Led direito

  // Iniciando Serial
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  e1 = digitalRead(pin_sensor1);
  e2 = digitalRead(pin_sensor2);
  me = digitalRead(pin_sensor3);
  d1 = digitalRead(pin_sensor4);
  d2 = digitalRead(pin_sensor5);

  seguidorBdsm();

}
