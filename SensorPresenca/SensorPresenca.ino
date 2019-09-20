//Sensor de presença

#define pinPIR 7
#define pin 10

void setup() {
  // put your setup code here, to run once:
  pinMode(pinPIR, INPUT);
  pinMode(pin, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  bool valorPIR = digitalRead(pinPIR);

  if(valorPIR){
    Serial.println("Detectado");
    digitalWrite(pin, HIGH);
  }else{
    Serial.println("Espaço vazio");
    digitalWrite(pin, LOW);
//    delay(1000);
  }
  
}
