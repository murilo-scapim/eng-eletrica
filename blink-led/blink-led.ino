void setup() {
  // Define o pino 13 como saída
  pinMode(13, OUTPUT);
}

void loop() {
  // Acende o led
  digitalWrite(13, HIGH);

  // espera por 1000 milissegundos (1 segundo)
  delay(1000);

  // Apaga o led
  digitalWrite(13, LOW);
  
  delay(1000);
}