#include <WiFi.h>
#include <PubSubClient.h>

const int LED_PIN = 2;

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
}

// =======================
// Quando chegar mensagem MQTT, executará essa função
// =======================
void callback(char* topic, byte* payload, unsigned int length) {

  String mensagem;

  for (int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }

  Serial.print("Mensagem recebida: ");
  Serial.println(mensagem);

  // =======================
  // CONTROLE DO LED
  // =======================
  if (mensagem == "ON") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED LIGADO");
  }

  if (mensagem == "OFF") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED DESLIGADO");
  }
}

// =======================
// RECONECTAR MQTT
// =======================
void reconnect() {

  while (!client.connected()) {

    Serial.print("Conectando MQTT...");

    String clientId = "ESP32-" + WiFi.macAddress();
    Serial.println(clientId);

    if (client.connect(clientId.c_str())) {

      Serial.println("conectado!");

      // Inscreve no tópico
      client.subscribe("LedControl");

    } else {

      Serial.print("falhou, rc=");
      Serial.print(client.state());

      delay(3000);
    }
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  setup_wifi();

  client.setServer(mqtt_server, 1883);

  // Define função callback
  client.setCallback(callback);
}


void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}