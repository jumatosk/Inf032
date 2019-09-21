//Semafóro de trânsito
#define vermelho 10
#define amarelo 9
#define verde 8

void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Verde
  digitalWrite(8, HIGH);
  delay(2000);
  digitalWrite(8, LOW);

  //Amarelo
  digitalWrite(9, HIGH);
  delay(2000);
  digitalWrite(9, LOW);

  //Vermelho
  digitalWrite(10, HIGH);
  delay(2000);
  digitalWrite(10, LOW);
}
