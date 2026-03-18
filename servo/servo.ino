#include <Servo.h>

Servo servo;
#define potPin A0 // Pino do potenciômetro
int valor;

void setup() {
  servo.attach(9); // Configura o pino D9 - pino de controle do servo
}

void loop() {
  valor = analogRead(potPin); // Leitura da tensão do pino A0
  valor = map(valor, 0, 1023, 0, 180); // Converte a leitura em número (0-180)
  servo.write(valor); // Controle PWM do servo
  delay(15); // Atraso de 15 milissegundos
}
