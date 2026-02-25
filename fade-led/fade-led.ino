#define PINLED 3

void setup() {
  pinMode(PINLED, OUTPUT);
}

void loop() {
  for (uint8_t i = 0; i < 255; i++) {

    // liga o led proporcionalmente ao valor de i
    analogWrite(PINLED, i);

    // aguarda 10 milissegundos (0.01 segundos)
    delay(10);                        
  }

  for (uint8_t i = 255; i > 0; i--) {
    analogWrite(PINLED, i);
    delay(10);
  }
}
