#define PINLED 3

void setup() {
  pinMode(PINLED, OUTPUT);
}

void loop() {
  for (uint8_t i = 0; i < 255; i++) {
    analogWrite(PINLED, i); // liga o led proporcionalmente ao valor de i
    delay(10); // aguarda 10 milissegundos                        
  }

  for (uint8_t i = 255; i > 0; i--) {
    analogWrite(PINLED, i);
    delay(10);
  }
}
