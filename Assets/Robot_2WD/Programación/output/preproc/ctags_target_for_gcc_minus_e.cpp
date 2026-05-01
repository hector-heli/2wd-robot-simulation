# 1 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260316_Encoder\\260316_Encoder.ino"
/*Monitor de Encoders

  Este programa se encarga de monitorear los encoders del robot y mostrar su conteo en el monitor serie. El conteo se actualiza cada vez que hay un cambio en los encoders, lo que permite observar el movimiento del robot en tiempo real.

*/
# 5 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260316_Encoder\\260316_Encoder.ino"
# 6 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260316_Encoder\\260316_Encoder.ino" 2

int rCountEncoder, lCountEncoder;
int rCountEncoderPrev, lCountEncoderPrev;
int trigger = 0;


void rightEncoder_ISR(){ rCountEncoder++;}
void leftEncoder_ISR(){ lCountEncoder++;}

void setup() {
  Serial.begin(9600); //iniciar puerto serie
  Serial.println("Iniciando monitor de encoders...");
  pinMode(3 , 0x0);
  pinMode(2 , 0x0);

  attachInterrupt(((3) == 2 ? 0 : ((3) == 3 ? 1 : -1)), rightEncoder_ISR, 2);
  attachInterrupt(((2) == 2 ? 0 : ((2) == 3 ? 1 : -1)), leftEncoder_ISR, 2);

}

void loop(){
  while(digitalRead(A0) && trigger == 0){}
  trigger = 1;

  if(rCountEncoder != rCountEncoderPrev || lCountEncoder != lCountEncoderPrev){
    Serial.print("Conteo izquierdo:  ");
    Serial.print(lCountEncoder);
    Serial.print("    Conteo derecho:  ");
    Serial.println(rCountEncoder);
    delay(10);
    rCountEncoderPrev = rCountEncoder;
    lCountEncoderPrev = lCountEncoder;
  }


}
