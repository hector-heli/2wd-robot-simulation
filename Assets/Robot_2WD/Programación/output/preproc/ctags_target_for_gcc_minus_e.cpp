# 1 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260417_ControlMotorPID\\260417_ControlMotorPID.ino"
# 2 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260417_ControlMotorPID\\260417_ControlMotorPID.ino" 2

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
const double constValue = 1; //3.1733;

void setup() {
  initializeRobot();
  printRobotStatus();
  lastTime = millis();
}

void loop() {
  if (BT.available()) {
    char cmd = (char)BT.read();
    inputString += cmd;
    if( cmd == '\n') stringComplete = true;
    Serial.println(cmd); // Debug
  }

  if(stringComplete) {
    for( int i =0; i<dataLength; i++) {
      int index = inputString.indexOf(separator);
      data[i]=inputString.substring(0,index).toInt();
      inputString = inputString.substring(index+1);
    }
    outValue1 = data[0];
    outValue2 = data[1];
    if(outValue1 > 0) controlMotor(0, outValue1); else controlMotor(0, -((outValue1)>0?(outValue1):-(outValue1)));
    if(outValue2 > 0) controlMotor(1, outValue2); else controlMotor(1, -((outValue2)>0?(outValue2):-(outValue2)));
    inputString = "";
    stringComplete = false;
  }

  if(millis()-lastTime >= sampleTime) {
    
# 48 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260417_ControlMotorPID\\260417_ControlMotorPID.ino" 3
   __asm__ __volatile__ ("cli" ::: "memory")
# 48 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260417_ControlMotorPID\\260417_ControlMotorPID.ino"
                 ;
    w1 =(constValue*lCountEncoder)/(millis()-lastTime);
    w2 =(constValue*rCountEncoder)/(millis()-lastTime);
    
# 51 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260417_ControlMotorPID\\260417_ControlMotorPID.ino" 3
   __asm__ __volatile__ ("sei" ::: "memory")
# 51 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\Motors\\260417_ControlMotorPID\\260417_ControlMotorPID.ino"
               ;
    lastTime = millis();
    lCountEncoder = 0;
    rCountEncoder = 0;
    Serial.print(">");
    Serial.print("v_derecha_rad_s");
    Serial.print(w1);
    Serial.print(",");
    Serial.print("v_izquierda_rad_s");
    Serial.print(w2);
    Serial.println("");
  }
}

void serialEvent() {
  while(Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if( inChar == '\n') stringComplete = true;
  }
}
