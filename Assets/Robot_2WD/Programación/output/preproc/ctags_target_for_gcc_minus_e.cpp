# 1 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
/* 

 * Control de un robot con Bluetooth HC-06 y L298N

 * 

 * Comandos:

 * F: Adelante

 * B: Atrás

 * L: Giro a la izquierda

 * R: Giro a la derecha

 * S: Disminuir velocidad rueda izquierda

 * T: Aumentar velocidad rueda izquierda

 * X: Disminuir velocidad rueda derecha

 * C: Aumentar velocidad rueda derecha

 * Velocidad máxima: 255

 * Velocidad mínima: 80

 * El programa utiliza la librería SoftwareSerial para comunicarse con el módulo Bluetooth HC-06, y controla los motores a través del driver L298N. La velocidad de cada rueda se puede ajustar individualmente mediante los comandos enviados desde el dispositivo Bluetooth, permitiendo el movimiento del robot



*/
# 19 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
# 20 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino" 2
# 21 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino" 2
SoftwareSerial BT(10, 11); // RX=11, TX=10 para HC-06

// Pines L298N Motores Izquierdos
int IN1 = 4;
int IN2 = 6;
int ENA = 5; // PWM

// Pines L298N Motores Derechos
int IN3 = 7;
int IN4 = 8;
int ENB = 9; // PWM

int velMax = 255, velMin = 80;

int rightWheelVelocity = 200, leftWheelVelocity = 200;

void setup() {
  Serial.begin(115200); // Debug
  BT.begin(9600); // HC-06
  for(int i=5; i<=9; i++ )pinMode(i, 0x1);
  for(int i=5; i<=9; i++ )digitalWrite(i, 0x0);
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();
    Serial.println(cmd); // Debug
    switch (cmd) {
      case 'F': front(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'B': back(); break;
      case 't': leftPlus(); break;
      case 'x': rightMinus(); break;
      case 's': leftMinus(); break;
      case 'c': rightPlus(); break;
      default: stop();
    }
    Serial.print(">");
    Serial.print("Vel_Izq:");
    Serial.print(leftWheelVelocity);
    Serial.print(",");
    Serial.print("Vel_Der:");
    Serial.print(rightWheelVelocity);
    Serial.println();
  }
}

void front() {
  digitalWrite(7, 0x0);
  digitalWrite(8, 0x1);
  analogWrite(9, rightWheelVelocity);

  digitalWrite(4, 0x1);
  digitalWrite(6, 0x0);
  analogWrite(5, leftWheelVelocity);
}

void back() {
  digitalWrite(7, 0x1);
  digitalWrite(8, 0x0);
  analogWrite(9, rightWheelVelocity);

  digitalWrite(4, 0x0);
  digitalWrite(6, 0x1);
  analogWrite(5, leftWheelVelocity);
}

void right() {
  digitalWrite(7, 0x0);
  digitalWrite(8, 0x0);
  analogWrite(9, rightWheelVelocity);

  digitalWrite(4, 0x1);
  digitalWrite(6, 0x0);
  analogWrite(5, leftWheelVelocity);
}

void left() {
  digitalWrite(7, 0x0);
  digitalWrite(8, 0x1);
  analogWrite(9, rightWheelVelocity);

  digitalWrite(4, 0x0);
  digitalWrite(6, 0x0);
  analogWrite(5, leftWheelVelocity);

}

void stop() {
  digitalWrite(IN1, 0x0); digitalWrite(IN2, 0x0); analogWrite(ENA, 0);
  digitalWrite(IN3, 0x0); digitalWrite(IN4, 0x0); analogWrite(ENB, 0);
}

void rightPlus(){ rightWheelVelocity < velMax? rightWheelVelocity += 10: rightWheelVelocity = velMax;}
void rightMinus(){ rightWheelVelocity > velMin? rightWheelVelocity -= 10: rightWheelVelocity = velMin;}
void leftPlus(){ leftWheelVelocity < velMax? leftWheelVelocity += 10: leftWheelVelocity = velMax;}
void leftMinus(){ leftWheelVelocity > velMin? leftWheelVelocity -= 10: leftWheelVelocity = velMin;}
