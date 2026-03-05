// Semáforos com Arduino
// Definições dos pinos onde os LEDs dos pedestres e veículos estão conectados
#define VERDE_PED 3
#define VERMELHO_PED 4
#define VERDE_VEI 5
#define AMARELO_VEI 6
#define VERMELHO_VEI 7

void setup() {
    pinMode(VERDE_PED, OUTPUT);
    pinMode(VERMELHO_PED, OUTPUT);
    pinMode(VERDE_VEI, OUTPUT);
    pinMode(AMARELO_VEI, OUTPUT);
    pinMode(VERMELHO_VEI, OUTPUT);
}

void loop() {
    digitalWrite(VERMELHO_VEI, LOW);   //Desliga o LED vermelho dos veículos
    digitalWrite(VERDE_VEI, HIGH);     //Liga o LED verde dos veículos
    digitalWrite(VERMELHO_PED, HIGH);  //Liga o LED vermelho dos pedestres
    delay(8000);

    digitalWrite(VERDE_VEI, LOW);      //Desliga o LED verde dos veículos
    digitalWrite(AMARELO_VEI, HIGH);   //Liga o LED amarelo do veículos
    delay(3000);

    digitalWrite(AMARELO_VEI, LOW);    //Desliga o LED amarelo dos veículos
    digitalWrite(VERMELHO_PED, LOW);   //Desliga o LED vermelho dos pedestres
    digitalWrite(VERMELHO_VEI, HIGH);  //Liga o LED vermelho dos veículos
    digitalWrite(VERDE_PED, HIGH);     //Liga o LED verde dos pedestres
    delay(5000);

    digitalWrite(VERDE_PED, LOW);      //Desliga o LED verde dos pedestres

    //Laço para piscar o LED vermelho dos pedestres
    for (int i = 0; i < 4; i++) {
        digitalWrite(VERMELHO_PED, HIGH);
        delay(250);
        digitalWrite(VERMELHO_PED, LOW);
        delay(250);
    }
}