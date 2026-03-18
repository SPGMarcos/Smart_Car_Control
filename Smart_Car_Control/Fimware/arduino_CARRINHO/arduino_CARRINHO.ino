#include <Servo.h>
#include <SoftwareSerial.h>

// Pinos da ponte H
#define IN3 4
#define IN4 5

// Servo e comunicação
#define SERVO_PIN 9
#define RX_ESP 0
#define TX_ESP 1
Servo direcao;
SoftwareSerial espSerial(RX_ESP, TX_ESP);

void setup() {
  Serial.begin(9600);          // Monitor Serial
  espSerial.begin(9600);       // Comunicação com ESP

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  direcao.attach(SERVO_PIN);
  direcao.write(80); // Centraliza servo

  Serial.println("🚗 Arduino pronto");
}

void loop() {
  if (espSerial.available()) {
    String comando = espSerial.readStringUntil('\n');
    comando.trim();
    comando.replace("\r", "");

    Serial.println("Comando recebido: " + comando);

    // Separar partes: direção + tração
    String parte1, parte2;
    int pos = comando.indexOf(',');
    if (pos != -1) {
      parte1 = comando.substring(0, pos);
      parte2 = comando.substring(pos + 1);
    } else {
      parte1 = comando;
      parte2 = "";
    }

    // Executa movimento
    executarComando(parte1);
    if (parte2 != "") executarComando(parte2);
  }
}

void executarComando(String cmd) {
  if (cmd == "F") {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if (cmd == "R") {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if (cmd == "P") {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  else if (cmd == "E") direcao.write(35);
  else if (cmd == "D") direcao.write(130);
  else if (cmd == "C") direcao.write(80);
  else Serial.println(cmd);
}
