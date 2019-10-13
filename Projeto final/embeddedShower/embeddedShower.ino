//Projeto: Embedded Shower
//Aluna: Juliana Matos
//Disciplina: Fundamentos de Sistemas Embarcados


//Definição das temperaturas
#define tempBaixaI 0
#define tempBaixaII 15
#define tempMediaI 16
#define tempMediaII 22
#define tempAlta 23

//Definição das portas digitaias dos LED's
#define temperaturaMinima 10
#define temperaturaMedia 9
#define temperaturaMaxima 8
#define agua 11

//Definição da porta do Sensor de presença
#define sensorPresenca 4

//Definição da porta do Sensor de temperatura
#define sensorTemperatura 2 //Porta digital
#define sensorTInterrupcao 0

//inclusão de biblioteca do sensor de temperatura
#include<idDHT11.h>

//Funções
void iniciaLeds();
void iniciaSensorPresenca();
int identificaPresenca();
void sensorTemperaturaWrapper(); //declaração da função de controle da interrupção
void loopDHT(); //atualiza a leitura do sensor
void tempoLigado();
void defineTempBaixa();
void defineTempMedia();
void defineTempAlta();
int defineGrausCelsius();

//Instanciação do objeto do sensor DHT11
idDHT11 DHT11(sensorTemperatura, sensorTInterrupcao, sensorTemperaturaWrapper);


void setup() {
  iniciaLeds();
  iniciaSensorPresenca();
  Serial.begin(9600);

}

//Variaveis do sensor de temperatura
float grausCelsius;

void loop() {
  int verificaPresenca = identificaPresenca();

  loopDHT();
  
  if (verificaPresenca == 1) {
    Serial.print("Temperatura do ambiente: ");
    Serial.print(grausCelsius);
    tempoLigado();
  }
}

void iniciaLeds() {
  pinMode(temperaturaMinima, OUTPUT);
  pinMode(temperaturaMedia, OUTPUT);
  pinMode(temperaturaMaxima, OUTPUT);
  pinMode(agua, OUTPUT);
}

void iniciaSensorPresenca() {
  pinMode(sensorPresenca, INPUT);
}

int identificaPresenca() {
  int verificaPresenca = 0;
  return verificaPresenca = digitalRead(sensorPresenca);
}

void sensorTemperaturaWrapper() {
  DHT11.isrCallback();
}

void loopDHT() {
#define tempoLeitura 1000
  static unsigned long delayLeitura = millis() + tempoLeitura + 5;
  static bool request = false;

  if ((millis() - delayLeitura) > tempoLeitura) {
    if (!request) {
      DHT11.acquire();
      request = true;
    }
  }

  if (request && !DHT11.acquiring()) {
    request = false;

    int result = DHT11.getStatus();

    switch (result)
    {
      case IDDHTLIB_OK:
        Serial.println("");
        break;
      case IDDHTLIB_ERROR_CHECKSUM:
        Serial.println("Erro\n\r\tErro Checksum");
        break;
      case IDDHTLIB_ERROR_ISR_TIMEOUT:
        Serial.println("Erro\n\r\tISR Time out");
        break;
      case IDDHTLIB_ERROR_RESPONSE_TIMEOUT:
        Serial.println("Erro\n\r\tResponse time out");
        break;
      case IDDHTLIB_ERROR_DATA_TIMEOUT:
        Serial.println("Erro\n\r\tData time out erro");
        break;
      case IDDHTLIB_ERROR_ACQUIRING:
        Serial.println("Erro\n\r\tAcquiring");
        break;
      case IDDHTLIB_ERROR_DELTA:
        Serial.println("Erro\n\r\tDelta time to small");
        break;
      case IDDHTLIB_ERROR_NOTSTARTED:
        Serial.println("Erro\n\r\tNao iniciado");
        break;
      default:
        Serial.println("Erro Desconhecido");
        break;
    }

    float valor = DHT11.getCelsius();

    if (!isnan(valor)) {
      grausCelsius = valor;
    }
    delayLeitura = millis();
  }
}

void tempoLigado() {
  if (grausCelsius >= tempBaixaI && grausCelsius <= tempBaixaII) {
    defineTempAlta();
  }

  else if (grausCelsius >= tempMediaI && grausCelsius <= tempMediaII) {
    defineTempMedia();
  }

  else if (grausCelsius >= tempAlta) {
    defineTempBaixa();
  }
}

void defineTempBaixa() {
  digitalWrite(temperaturaMinima, HIGH);
  digitalWrite(agua, HIGH);
  delay(20000);
  digitalWrite(temperaturaMinima, LOW);
  digitalWrite(agua, LOW);
  delay(10000);
}

void defineTempMedia() {
  digitalWrite(temperaturaMedia, HIGH);
  digitalWrite(agua, HIGH);
  delay(15000);
  digitalWrite(temperaturaMedia, LOW);
  digitalWrite(agua, LOW);
  delay(15000);
}

void defineTempAlta() {
  digitalWrite(temperaturaMaxima, HIGH);
  digitalWrite(agua, HIGH);
  delay(10000);
  digitalWrite(temperaturaMaxima, LOW);
  digitalWrite(agua, LOW);
  delay(20000);
}
