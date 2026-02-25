#include <LiquidCrystal.h>

// Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

uint8_t contador = 0;

void setup() {
  // Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
}

void loop(){
  lcd.clear();

  // Posiciona o cursor na coluna 3, linha 0
  lcd.setCursor(3, 0);

  lcd.print("Boa noite!");

  lcd.setCursor(3, 1);
  
  lcd.print(contador);
  contador++;

  if (contador == 60) {
    contador = 0;
  }
  
  delay(1000);
}