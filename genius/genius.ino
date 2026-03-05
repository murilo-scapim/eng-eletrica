#include <EEPROM.h>

// Definindo as notas para os sons
#define NOTE_D4  294
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_A5  880

// Criando o array para os 4 sons para sortear um som
int tons[4] = { NOTE_A5, NOTE_A4, NOTE_G4, NOTE_D4 };

// Nossa sequência de até 100 itens vai começar vazia.
int sequencia[100] = {};

// Indica a rodada atual que o jogo se encontra.
int rodada_atual = 0;

// Indica o passo atual dentro da sequência, é usado enquanto a sequência
// está sendo reproduzida.
int passo_atual_na_sequencia = 0;

// Pinos de áudio, leds e botões.
int pinoBuzzer = 12;
int pinosLeds[4] = { 2, 4, 6, 8 };
int pinosBotoes[4] = { 3, 5, 7, 9 };

// Flag indicando se o botão foi pressionado durante o loop principal.
int botao_pressionado = 0;

// Flag indicando se o jogo acabou.
int perdeu_o_jogo = false;

// Endereço da EEPROM para armazenar o recorde
int enderecoRecorde = 0;

// Variável para armazenar o recorde atual
int recorde = 0;

void setup() {
  // Inicializando o Serial Monitor
  Serial.begin(9600);

  // Definindo o modo dos pinos dos Leds como saída
  for (int i = 0; i <= 3; i++) {
    pinMode(pinosLeds[i], OUTPUT);
  }

  // Definindo o modo dos pinos dos Botões como pullup interno
  // Mantem o pino em HIGH
  for (int i = 0; i <= 3; i++) {
    pinMode(pinosBotoes[i], INPUT_PULLUP);
  }

  // Definindo o modo do pino do buzzer como saída
  pinMode(pinoBuzzer, OUTPUT);

  // Inicializando o random através de uma leitura da porta analógica A0
  randomSeed(analogRead(0));

  // Recupera o recorde da EEPROM
  recorde = EEPROM.read(enderecoRecorde);

  // Exibe o recorde atual no monitor serial
  Serial.print("Recorde atual: ");
  Serial.println(recorde);
}

void loop() {
  // Se perdeu o jogo reinicializamos todas as variáveis
  if (perdeu_o_jogo) {
    int sequencia[100] = {};
    rodada_atual = 0;
    passo_atual_na_sequencia = 0;
    perdeu_o_jogo = false;
  }

  // Toca um som de início para anunciar que o jogo está começando quando é a primeira rodada
  if (rodada_atual == 0) {
    Serial.println("Vamos começar! Memorize a sequência!");
    tocarSomDeInicio();
    delay(500);
  }

  // Chama a função que inicializa a próxima rodada.
  proximaRodada();
  // Reproduz a sequência atual.
  reproduzirSequencia();
  // Aguarda os botões serem pressionados pelo jogador.
  aguardarJogador();

  // Verifica se o jogador chegou ao recorde
  if (rodada_atual > recorde) {
    recorde = rodada_atual;
    EEPROM.write(enderecoRecorde, recorde);
    Serial.print("Novo Recorde: ");
    Serial.println(recorde);
  }

  // Aguarda 1 segundo entre cada jogada.
  delay(1000);
}

// Sorteia um novo item e adiciona na sequência
void proximaRodada() {
  int numero_sorteado = random(0, 4);
  sequencia[rodada_atual++] = numero_sorteado;
}

// Reproduz a sequência para ser memorizada.
void reproduzirSequencia() {
  for (int i = 0; i < rodada_atual; i++) {
    tone(pinoBuzzer, tons[sequencia[i]]);
    digitalWrite(pinosLeds[sequencia[i]], HIGH);
    delay(500);
    noTone(pinoBuzzer);
    digitalWrite(pinosLeds[sequencia[i]], LOW);
    delay(100);
  }
  noTone(pinoBuzzer);
}

// Aguarda o jogador iniciar sua jogada.
void aguardarJogador() {
  for (int i = 0; i < rodada_atual; i++) {
    aguardarJogada();
    
    // Verifica a jogada  
    if (sequencia[passo_atual_na_sequencia] != botao_pressionado) {
      gameOver(); // Perdeu
    }
   
    // Se perdeu, encerra o jogo
    if (perdeu_o_jogo) {
      break;
    }
    passo_atual_na_sequencia++;
  }

  // Redefine a variável para 0.
  passo_atual_na_sequencia = 0;
}

void aguardarJogada() {
  boolean jogada_efetuada = false;
  while (!jogada_efetuada) {
    for (int i = 0; i <= 3; i++) {
      if (!digitalRead(pinosBotoes[i])) {
        // Dizendo qual foi o botão pressionado.
        botao_pressionado = i;

        tone(pinoBuzzer, tons[i]);
        digitalWrite(pinosLeds[i], HIGH);
        delay(300);
        digitalWrite(pinosLeds[i], LOW);
        noTone(pinoBuzzer);

        jogada_efetuada = true;
      }
    }
    delay(10);
  }
}

void gameOver() {
    // GAME OVER.
    Serial.println("Game Over!");
    
    // Verifica se o jogador superou o recorde.
    if (rodada_atual > recorde) {
        recorde = rodada_atual;  // Atualiza o recorde
        EEPROM.write(enderecoRecorde, recorde);  // Grava o novo recorde na EEPROM
        Serial.print("Novo Recorde: ");
        Serial.println(recorde);  // Exibe no serial o novo recorde
    }

    // Reproduz sons e acende LEDs para indicar o game over.
    for (int i = 0; i <= 3; i++) {
      tone(pinoBuzzer, tons[i]);
      digitalWrite(pinosLeds[i], HIGH);
      delay(200);
      digitalWrite(pinosLeds[i], LOW);
      noTone(pinoBuzzer);
    }

    // Mais um som de game over, com todos os LEDs acesos piscando.
    tone(pinoBuzzer, tons[3]);
    for (int i = 0; i <= 3; i++) {
      digitalWrite(pinosLeds[0], HIGH);
      digitalWrite(pinosLeds[1], HIGH);
      digitalWrite(pinosLeds[2], HIGH);
      digitalWrite(pinosLeds[3], HIGH);
      delay(100);
      digitalWrite(pinosLeds[0], LOW);
      digitalWrite(pinosLeds[1], LOW);
      digitalWrite(pinosLeds[2], LOW);
      digitalWrite(pinosLeds[3], LOW);
      delay(100);
    }
    
    // Apaga o som e define perdeu o jogo como true
    noTone(pinoBuzzer);
    perdeu_o_jogo = true;
}

void tocarSomDeInicio() {
  tone(pinoBuzzer, tons[0]);
  digitalWrite(pinosLeds[0], HIGH);
  digitalWrite(pinosLeds[1], HIGH);
  digitalWrite(pinosLeds[2], HIGH);
  digitalWrite(pinosLeds[3], HIGH);
  delay(500);
  digitalWrite(pinosLeds[0], LOW);
  digitalWrite(pinosLeds[1], LOW);
  digitalWrite(pinosLeds[2], LOW);
  digitalWrite(pinosLeds[3], LOW);
  delay(500);
  noTone(pinoBuzzer);
}