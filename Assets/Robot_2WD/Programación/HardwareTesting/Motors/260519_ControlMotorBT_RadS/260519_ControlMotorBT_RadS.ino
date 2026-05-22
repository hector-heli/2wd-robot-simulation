#include <robot_config.h>

float frontVelocity, angularVelocity;
/////////////////////////// COMUNICACION SERIAL //////////////////
String inputString = "";
bool stringComplete = false;
const char separator = ',';
const int dataLength = 2;
int data[dataLength];

//////////////////////// TIEMPO DE MUESTREO ///////////////
unsigned long lastTime, sampleTime = 100;

int outValue1 = 0;
int outValue2 = 0;
double w1 = 0.0, w2 = 0.0;
const double constValue = (2*PI*1000) / (ENCODER_PPR);//3.1733;

void setup() {
  initializeRobot();
  printRobotStatus();
  lastTime = millis();
}

void loop() {
  // Serial.println(BT.available());
  if (BT.available()) {
    char cmd = (char)BT.read();
    inputString += cmd;
    delay(1); // Pequeña pausa para evitar saturar el loop

    if( BT.available() == 0) {
      stringComplete = true;   
      Serial.println(inputString);  // Debug
    }
  }

  if(stringComplete) {
    for( int i=0; i<dataLength; i++) {
      int index = inputString.indexOf(separator);
      data[i]=inputString.substring(0,index).toInt();
      inputString = inputString.substring(index+1);
    }
    outValue1 = data[0];
    outValue2 = data[1];
    if(outValue1 > 0) controlMotor(0, outValue1); else controlMotor(0, -abs(outValue1));
    if(outValue2 > 0) controlMotor(1, outValue2); else controlMotor(1, -abs(outValue2));
    inputString = "";
    stringComplete = false;
  }

  if(millis()-lastTime >= sampleTime) {
    noInterrupts();
    w1 =(constValue*lCountEncoder)/(millis()-lastTime);
    w2 =(constValue*rCountEncoder)/(millis()-lastTime);
    interrupts();
    Serial.print(">");
    Serial.print("v_derecha_rad_s:");
    Serial.print(w1);
    Serial.print(",");
    Serial.print("v_izquierda_rad_s:");
    Serial.print(w2);
    Serial.println("");
    lCountEncoder = 0;
    rCountEncoder = 0;
    lastTime = millis();
  }
}

void serialEvent() {
  while(Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if( inChar == '\n') stringComplete = true;   
  }
}
