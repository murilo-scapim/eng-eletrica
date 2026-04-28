#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHTesp.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT22
#define DHT_PIN 15
DHTesp dhtSensor;

#define GAS_PIN 34
#define BUZZER_PIN 25

#define LED_R 14
#define LED_G 26
#define LED_B 32

int limiteGas = 2000;

// controla cor do LED RGB
void setColor(bool r, bool g, bool b) {
  digitalWrite(LED_R, r);
  digitalWrite(LED_G, g);
  digitalWrite(LED_B, b);
}

void setup() {
    Serial.begin(115200); // define a velocidade de comunicação serial entre o ESP32 e o computador
  // 115200 bits por segundo (baud rate) Velocidade com que os dados são enviados pela porta serial

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  Wire.begin(21, 22); // inicialização do barramento I2C no ESP32
  // 21 = SDA (dados) e 22 = SCL (clock)

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erro no OLED");
    while (true);
  }

  display.clearDisplay();
}

void loop() {
  // leitura DHT22
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  float temperatura = data.temperature;
  float umidade = data.humidity;

  int gas = analogRead(GAS_PIN);

  bool alertaGas = (gas > limiteGas);
  bool atencaoGas = (gas > limiteGas * 0.7);

  // buzzer
  digitalWrite(BUZZER_PIN, alertaGas);

  // LED RGB (status)
  if (alertaGas) {
    setColor(1, 0, 0); // vermelho
  } else if (atencaoGas) {
    setColor(1, 1, 0); // amarelo
  } else {
    setColor(0, 1, 0); // verde
  }

  // OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.printf("Temp: %.2f C\n", temperatura);
  display.printf("Hum : %.1f %%\n", umidade);
  display.printf("Gas : %d\n", gas);
  display.print("Status: ");
  display.println(alertaGas ? "ALERTA!" : (atencaoGas ? "ATENCAO" : "Normal"));

  display.display();

  // Serial debug
  Serial.printf("Temp: %.2f C\n", temperatura);
  Serial.printf("Hum : %.1f %%\n", umidade);
  Serial.printf("Gas : %d\n", gas);
  Serial.println("---");

  delay(2000);
}