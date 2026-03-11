Sensor ultrassônico mostrando distância no Serial Monitor

// Pinos do sensor
const uint8_t PinTrigger = 8;
const uint8_t PinEcho = 9;

// Variável para armazenar o tempo de retorno do eco
float TempoEcho = 0;

// Velocidade do som
const float velocidadeSom_mps = 340;       // metros por segundo
const float velocidadeSom_mpus = 0.000340; // metros por microssegundo

void setup() {

  pinMode(PinTrigger, OUTPUT); // pino que envia o pulso ultrassônico
  digitalWrite(PinTrigger, LOW);

  pinMode(PinEcho, INPUT); // pino que recebe o eco

  Serial.begin(9600); // inicia comunicação com Serial Monitor
  delay(100);
}

void loop(){

  DisparaPulsoUltrassonico(); // envia pulso ultrassônico

  // mede o tempo que o eco levou para voltar
  TempoEcho = pulseIn(PinEcho, HIGH);

  // mostra distância em metros
  Serial.print("Metros: ");
  Serial.println(CalculaDistancia(TempoEcho));

  // mostra distância em centímetros
  Serial.print("Cm: ");
  Serial.println(CalculaDistancia(TempoEcho) * 100);

  Serial.println("-------------------");

  delay(2000); // atualiza a cada 2 segundos
}

// função que envia o pulso de 10 microsegundos
void DisparaPulsoUltrassonico() {
  digitalWrite(PinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger, LOW);
}

// calcula a distância usando o tempo do eco
float CalculaDistancia(float tempo_us) {
  return ((tempo_us * velocidadeSom_mpus) / 2); 
  // divide por 2 porque o som vai até o objeto e volta
}