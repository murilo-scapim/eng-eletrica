#define PINLED 13

void setup() {
  // Define o pino 13 como saída
  pinMode(PINLED, OUTPUT);
}

void loop() {
  // Acende o led
  digitalWrite(PINLED, HIGH);

  // espera por 1000 milissegundos (1 segundo)
  delay(1000);

  // Apaga o led
  digitalWrite(PINLED, LOW);
  
  delay(1000);
}