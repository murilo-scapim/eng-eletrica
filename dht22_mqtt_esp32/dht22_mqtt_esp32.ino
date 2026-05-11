#include <WiFi.h>          // Biblioteca para conexão WiFi
#include <PubSubClient.h>  // Biblioteca para MQTT
#include "DHTesp.h"        // Biblioteca para sensor DHT22/DHT11

const int DHT_PIN = 23;   // Pino onde o sensor DHT está conectado
DHTesp dhtSensor;         // Cria objeto do sensor DHT

// Dados da rede WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Broker MQTT público
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;           // Cliente WiFi para MQTT
PubSubClient client(espClient); // Cliente MQTT

// Função para conectar o ESP32 à rede WiFi
void setup_wifi() {
  delay(10);
  WiFi.mode(WIFI_STA);          // Coloca o WiFi em modo estação
  WiFi.begin(ssid, password);   // Inicia conexão WiFi

  // Espera até conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");
}

// Função para reconectar ao broker MQTT caso a conexão caia
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");

    String clientId = "ESP32-" + WiFi.macAddress();
    
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!"); // Conexão bem-sucedida
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state()); // Mostra erro de conexão
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  setup_wifi();          // Conecta à rede WiFi
  client.setServer(mqtt_server, 1883); // Define servidor MQTT

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22); // Inicializa sensor DHT22
}

void loop() {
  if (!client.connected()) reconnect(); // Verifica conexão MQTT
  client.loop();                        // Mantém MQTT ativo

  TempAndHumidity data = dhtSensor.getTempAndHumidity(); // Lê temperatura e umidade

  String temp = String(data.temperature, 2); // Converte temperatura para string com 2 casas decimais
  String hum  = String(data.humidity, 2);    // Converte umidade para string com 2 casas decimais

  // Publica dados no broker MQTT
  client.publish("wokwi/dht/temperatura", temp.c_str());
  client.publish("wokwi/dht/umidade", hum.c_str());

  // Exibe dados no monitor serial
  Serial.println("Temp: " + temp);
  Serial.println("Umidade: " + hum);

  delay(2000); // Espera 2 segundos antes da próxima leitura
}