#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A5
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS = 2000;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  dht.begin();
}

void loop() {
  delay(delayMS);

  sensors_event_t event;
  
  dht.temperature().getEvent(&event);

  if (isnan(event.temperature)) {
    Serial.println("Erro na leitura da temperatura!");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(event.temperature, 1);
    lcd.write(223); // simbolo do grau
    lcd.print("C");
  }

  dht.humidity().getEvent(&event);

  if (isnan(event.relative_humidity)) {
    Serial.println("Erro na leitura da umidade!");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Umid: ");
    lcd.print(event.relative_humidity, 1);
    lcd.print("%");
  }
}