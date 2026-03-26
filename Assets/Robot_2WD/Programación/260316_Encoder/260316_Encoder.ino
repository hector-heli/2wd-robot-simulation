#define   rightEncoderPin  3
#define   leftEncoderPin   2 
    
int valueDer = 0, valueIzq = 0;
int rCountEncoder, lCountEncoder;

void rightEncoder_ISR(){ rCountEncoder++;}
void leftEncoder_ISR(){ lCountEncoder++;}

void setup() {
  Serial.begin(9600); //iniciar puerto serie
  pinMode(rightEncoderPin , INPUT);
  pinMode(leftEncoderPin , INPUT);

  attachInterrupt(digitalPinToInterrupt(rightEncoderPin), rightEncoder_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(leftEncoderPin), leftEncoder_ISR, FALLING);

}

void loop(){
  Serial.print("Conteo izquierdo:  ");
  Serial.print(lCountEncoder);
  Serial.print("    Conteo derecho:  ");
  Serial.println(rCountEncoder);
  delay(10);
}

