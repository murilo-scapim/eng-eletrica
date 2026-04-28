#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// API
String apiKey = "cab696218a79e06a917613d18a2a865e";
String cidade = "Ituverava,BR";

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Variáveis globais
float temp = 0;
float umidade = 0;
String clima = "";

// WiFi
void conectarWiFi() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Conectando WiFi...");
  display.display();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

bool obterClima() {

  HTTPClient http;

  String url = "http://api.openweathermap.org/data/2.5/weather?q=" 
               + cidade + "&APPID=" + apiKey + "&units=metric&lang=pt_br";

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode != 200) {
    http.end();
    return false;
  }

  String payload = http.getString();
  http.end();

  DynamicJsonDocument doc(1024);

  // Caso dê erro
  if (deserializeJson(doc, payload)) {
    return false;
  }

  temp = doc["main"]["temp"];
  umidade = doc["main"]["humidity"];
  clima = doc["weather"][0]["description"] | "";

  return true;
}

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  conectarWiFi();
}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    conectarWiFi();
    return;
  }

  if (obterClima()) {

    display.clearDisplay();
    display.setCursor(0,0);

    display.println(cidade);

    display.print("Temp: ");
    display.print(temp);
    display.println(" C");

    display.print("Umid: ");
    display.print(umidade);
    display.println("%");

    display.println(clima);

    display.display();

  } else {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Erro!");
    display.display();
  }

  delay(10000);
}