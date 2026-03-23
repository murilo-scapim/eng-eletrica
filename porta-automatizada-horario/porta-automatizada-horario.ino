#include <Servo.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <EEPROM.h>

// --- CONFIGURAÇÕES DE HARDWARE ---
Servo servoMotor;
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço I2C do LCD

// --- CONFIGURAÇÃO DO KEYPAD 4x4 ---
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- VARIÁVEIS DE HORÁRIOS ---
int openHour, openMin;    // Hora de abrir
int closeHour, closeMin;  // Hora de fechar

// --- SETUP ---
void setup() {
  // Inicializa servo e LCD
  servoMotor.attach(10);
  lcd.init();
  lcd.backlight();

  rtc.begin();

  // Carregar horários salvos na EEPROM
  openHour = EEPROM.read(0);
  openMin  = EEPROM.read(1);
  closeHour = EEPROM.read(2);
  closeMin  = EEPROM.read(3);

  lcd.print("Porta Automatica");
  delay(2000);
  lcd.clear();
}

// --- LOOP PRINCIPAL ---
void loop() {
  DateTime now = rtc.now();

  // Exibir hora atual no LCD
  displayTime(now.hour(), now.minute());

  // Controle da porta
  controlDoor(now.hour(), now.minute());

  // Leitura do teclado
  char key = keypad.getKey();
  if(key == 'A') setDoorTime(0); // Configurar abertura
  if(key == 'B') setDoorTime(1); // Configurar fechamento

  delay(500);
}

// --- FUNÇÃO PARA EXIBIR HORA ---
void displayTime(int hour, int minute){
  lcd.setCursor(0,0);
  lcd.print("Hora: ");
  if(hour < 10) lcd.print('0');
  lcd.print(hour);
  lcd.print(':');
  if(minute < 10) lcd.print('0');
  lcd.print(minute);
}

// --- FUNÇÃO PARA CONTROLAR PORTA ---
void controlDoor(int hourNow, int minNow){
  lcd.setCursor(0,1);

  if(hourNow == openHour && minNow == openMin){
    servoMotor.write(90); // Abrir
    lcd.print("Porta: Aberta  ");
  } else if(hourNow == closeHour && minNow == closeMin){
    servoMotor.write(0);  // Fechar
    lcd.print("Porta: Fechada ");
  }
}

// --- FUNÇÃO PARA CONFIGURAR HORÁRIOS ---
void setDoorTime(int mode){
  lcd.clear();
  if(mode == 0) lcd.print("HHMM Abrir:");
  else lcd.print("HHMM Fechar:");

  String input = "";
  while(input.length() < 4){
    char key = keypad.getKey();
    if(key){
      input += key;
      lcd.setCursor(input.length()-1,1);
      lcd.print(key);
    }
  }

  int h = input.substring(0,2).toInt();
  int m = input.substring(2,4).toInt();

  if(mode == 0){
    openHour = h;
    openMin = m;
    EEPROM.write(0,h);
    EEPROM.write(1,m);
  } else {
    closeHour = h;
    closeMin = m;
    EEPROM.write(2,h);
    EEPROM.write(3,m);
  }

  lcd.clear();
  lcd.print("Horario Salvo!");
  delay(1000);
  lcd.clear();
}