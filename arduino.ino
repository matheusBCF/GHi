#include <Servo.h>

// Objetos dos servos
Servo servo1;
Servo servo2;

// Pinos
const int PINO_SERVO1 = 9;
const int PINO_SERVO2 = 10;

const int PINO_LED1 = 6;
const int PINO_LED2 = 7;

// Variável para receber os comandos
String comando = "";

void setup() {

  // Inicia comunicação serial
  Serial.begin(9600);

  // Liga os servos aos pinos
  servo1.attach(PINO_SERVO1);
  servo2.attach(PINO_SERVO2);

  // Configura os LEDs
  pinMode(PINO_LED1, OUTPUT);
  pinMode(PINO_LED2, OUTPUT);

  // Estado inicial
  digitalWrite(PINO_LED1, LOW);
  digitalWrite(PINO_LED2, LOW);

  servo1.write(90);
  servo2.write(90);

  Serial.println("Arduino pronto!");
}

void loop() {

  // Verifica se chegou algum comando
  if (Serial.available() > 0) {

    comando = Serial.readStringUntil('\n');

    comando.trim();

    processarComando(comando);
  }
}

void processarComando(String cmd) {

  // --------------------------------
  // SERVO 1
  // --------------------------------
  if (cmd.startsWith("S1:")) {

    int angulo = cmd.substring(3).toInt();

    // Garante que o valor fique entre 0 e 180
    angulo = constrain(angulo, 0, 180);

    servo1.write(angulo);

    // Acende LED 1
    digitalWrite(PINO_LED1, HIGH);

    Serial.print("Servo 1: ");
    Serial.println(angulo);
  }

  // --------------------------------
  // SERVO 2
  // --------------------------------
  else if (cmd.startsWith("S2:")) {

    int angulo = cmd.substring(3).toInt();

    // Garante que o valor fique entre 0 e 180
    angulo = constrain(angulo, 0, 180);

    servo2.write(angulo);

    // Acende LED 2
    digitalWrite(PINO_LED2, HIGH);

    Serial.print("Servo 2: ");
    Serial.println(angulo);
  }

  // --------------------------------
  // PARAR SERVO 1
  // --------------------------------
  else if (cmd == "P1") {

    digitalWrite(PINO_LED1, LOW);

    Serial.println("Servo 1 parado");
  }

  // --------------------------------
  // PARAR SERVO 2
  // --------------------------------
  else if (cmd == "P2") {

    digitalWrite(PINO_LED2, LOW);

    Serial.println("Servo 2 parado");
  }
}