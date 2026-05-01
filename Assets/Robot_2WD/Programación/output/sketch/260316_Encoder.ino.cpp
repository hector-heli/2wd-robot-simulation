#include <Arduino.h>
#line 1 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260316_Encoder\\260316_Encoder.ino"
/*Monitor de Encoders
  Este programa se encarga de monitorear los encoders del robot y mostrar su conteo en el monitor serie. El conteo se actualiza cada vez que hay un cambio en los encoders, lo que permite observar el movimiento del robot en tiempo real.
*/

#include <mapping.h>   

int rCountEncoder, lCountEncoder;
int rCountEncoderPrev, lCountEncoderPrev;
int trigger = 0;


#line 12 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260316_Encoder\\260316_Encoder.ino"
void rightEncoder_ISR();
#line 13 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260316_Encoder\\260316_Encoder.ino"
void leftEncoder_ISR();
#line 15 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260316_Encoder\\260316_Encoder.ino"
void setup();
#line 26 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260316_Encoder\\260316_Encoder.ino"
void loop();
#line 12 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260316_Encoder\\260316_Encoder.ino"
void rightEncoder_ISR(){ rCountEncoder++;}
void leftEncoder_ISR(){ lCountEncoder++;}

void setup() {
  Serial.begin(9600); //iniciar puerto serie
  Serial.println("Iniciando monitor de encoders...");
  pinMode(RIGHT_ENCODER , INPUT);
  pinMode(LEFT_ENCODER , INPUT);

  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), rightEncoder_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), leftEncoder_ISR, FALLING);

}

void loop(){
  while(digitalRead(RIGHT_IR_SENSOR) && trigger == 0){}
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


