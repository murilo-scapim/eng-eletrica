#include <LiquidCrystal.h>

// Pinos do sensor ultrassônico
const uint8_t PinTrigger = 8;
const uint8_t PinEcho = 9;

// Variável para armazenar o tempo de retorno do eco
float TempoEcho = 0;

// Velocidade do som no ar
const float velocidadeSom_mps = 340;      // metros por segundo
const float velocidadeSom_mpus = 0.000340; // metros por microssegundo (usada no cálculo)

// Inicializa o LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2); // Inicia LCD 16x2

  pinMode(PinTrigger, OUTPUT); // Trigger envia o pulso ultrassônico
  digitalWrite(PinTrigger, LOW);

  pinMode(PinEcho, INPUT); // Echo recebe o pulso refletido

  Serial.begin(9600); // Inicia comunicação serial (para monitoramento)
  delay(100);
}

void loop(){

  DisparaPulsoUltrassonico(); // Envia pulso ultrassônico

  // Mede o tempo que o sinal levou para voltar
  TempoEcho = pulseIn(PinEcho, HIGH);
  
  // Mostra distância em metros no LCD
  lcd.setCursor(0, 0);
  lcd.print("Metros: ");
  lcd.print(CalculaDistancia(TempoEcho));

  // Mostra distância em centímetros
  lcd.setCursor(0, 1);
  lcd.print("Cm: ");
  lcd.print(CalculaDistancia(TempoEcho) * 100);

  delay(2000); // Atualiza a cada 2 segundos
}

// Função que dispara o pulso ultrassônico (10 microsegundos)
void DisparaPulsoUltrassonico() {
  digitalWrite(PinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger, LOW);
}

// Calcula a distância com base no tempo do eco
float CalculaDistancia(float tempo_us) {
  return ((tempo_us * velocidadeSom_mpus) / 2); 
  // divide por 2 porque o som vai e volta
}