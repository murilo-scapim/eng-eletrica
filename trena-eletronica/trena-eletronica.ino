#include <LiquidCrystal.h>

const uint8_t PinTrigger = 8;
const uint8_t PinEcho = 9;
float TempoEcho = 0;
const float velocidadeSom_mps = 340;
const float velocidadeSom_mpus = 0.000340;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  pinMode(PinTrigger, OUTPUT);
  digitalWrite(PinTrigger, LOW);
  pinMode(PinEcho, INPUT);
  Serial.begin(9600);
  delay(100);
}

void loop(){
  DisparaPulsoUltrassonico();

  TempoEcho = pulseIn(PinEcho, HIGH);
  
  lcd.setCursor(0, 0);
  lcd.print("Metros: ");
  lcd.print(CalculaDistancia(TempoEcho));

  lcd.setCursor(0, 1);
  lcd.print("Cm: ");
  lcd.print(CalculaDistancia(TempoEcho) * 100);
  delay(2000);
}

void DisparaPulsoUltrassonico() {
  digitalWrite(PinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger, LOW);
}

float CalculaDistancia(float tempo_us) {
  return ((tempo_us * velocidadeSom_mpus) / 2);
}