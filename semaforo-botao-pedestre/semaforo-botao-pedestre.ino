#define VERDE_PED 3
#define VERMELHO_PED 4
#define VERDE_VEI 5
#define AMARELO_VEI 6
#define VERMELHO_VEI 7
#define BOTAO 2

bool botaoPressionado = false;

void setup() {

  pinMode(VERDE_PED, OUTPUT);
  pinMode(VERMELHO_PED, OUTPUT);
  pinMode(VERDE_VEI, OUTPUT);
  pinMode(AMARELO_VEI, OUTPUT);
  pinMode(VERMELHO_VEI, OUTPUT);

  pinMode(BOTAO, INPUT_PULLUP);

}

void loop() {

  // verifica botão
  if (digitalRead(BOTAO) == LOW) {
    botaoPressionado = true;
  }

  // VEÍCULOS VERDE
  digitalWrite(VERDE_VEI, HIGH);
  digitalWrite(VERMELHO_PED, HIGH);
  digitalWrite(VERMELHO_VEI, LOW);

  delay(8000);

  // se pedestre solicitou
  if (botaoPressionado) {

    // AMARELO VEÍCULOS
    digitalWrite(VERDE_VEI, LOW);
    digitalWrite(AMARELO_VEI, HIGH);

    delay(3000);

    digitalWrite(AMARELO_VEI, LOW);

    // VERMELHO VEÍCULOS / VERDE PEDESTRE
    digitalWrite(VERMELHO_VEI, HIGH);
    digitalWrite(VERMELHO_PED, LOW);
    digitalWrite(VERDE_PED, HIGH);

    delay(4000);

    // restante do tempo do pedestre
    delay(3000);

    digitalWrite(VERDE_PED, LOW);

    // vermelho pedestre piscando
    for (int i = 0; i < 4; i++) {
      digitalWrite(VERMELHO_PED, HIGH);
      delay(500);
      digitalWrite(VERMELHO_PED, LOW);
      delay(500);
    }

    digitalWrite(VERMELHO_PED, HIGH);

    botaoPressionado = false;
  }
}