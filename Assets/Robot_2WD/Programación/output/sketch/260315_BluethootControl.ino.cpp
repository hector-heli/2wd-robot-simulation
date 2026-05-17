#include <Arduino.h>
#line 1 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
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

#include <mapping.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(BT_TX_PIN, BT_RX_PIN);  // RX=11, TX=10 para HC-06

// Pines L298N Motores Izquierdos
int IN1 = LEFT_MOTOR_IN1;
int IN2 = LEFT_MOTOR_IN2;
int ENA = LEFT_MOTOR_ENA;  // PWM

// Pines L298N Motores Derechos
int IN3 = RIGHT_MOTOR_IN3;
int IN4 = RIGHT_MOTOR_IN4;
int ENB = RIGHT_MOTOR_ENB; // PWM

int velMax = 255, velMin = 80;

int rightWheelVelocity = 200, leftWheelVelocity = 200;

#line 37 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void setup();
#line 44 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void loop();
#line 69 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void front();
#line 79 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void back();
#line 89 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void right();
#line 99 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void left();
#line 110 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void stop();
#line 115 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void rightPlus();
#line 116 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void rightMinus();
#line 117 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void leftPlus();
#line 118 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void leftMinus();
#line 37 "C:\\Users\\hh_rg\\OneDrive\\Escritorio\\2WD Robot Simulation\\Assets\\Robot_2WD\\Programación\\HardwareTesting\\ControlTesting\\260315_BluethootControl\\260315_BluethootControl.ino"
void setup() {
  Serial.begin(115200);  // Debug
  BT.begin(9600);      // HC-06
  for(int i=5; i<=9; i++ )pinMode(i, OUTPUT);
  for(int i=5; i<=9; i++ )digitalWrite(i, LOW);
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();
    Serial.println(cmd);  // Debug
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
  digitalWrite(RIGHT_MOTOR_IN3, LOW);  
  digitalWrite(RIGHT_MOTOR_IN4, HIGH); 
  analogWrite(RIGHT_MOTOR_ENB, rightWheelVelocity);

  digitalWrite(LEFT_MOTOR_IN1, HIGH);  
  digitalWrite(LEFT_MOTOR_IN2, LOW); 
  analogWrite(LEFT_MOTOR_ENA, leftWheelVelocity);
}

void back() {
  digitalWrite(RIGHT_MOTOR_IN3, HIGH);  
  digitalWrite(RIGHT_MOTOR_IN4, LOW); 
  analogWrite(RIGHT_MOTOR_ENB, rightWheelVelocity);

  digitalWrite(LEFT_MOTOR_IN1, LOW);  
  digitalWrite(LEFT_MOTOR_IN2, HIGH); 
  analogWrite(LEFT_MOTOR_ENA, leftWheelVelocity);
}
  
void right() {
  digitalWrite(RIGHT_MOTOR_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_IN4, LOW);
  analogWrite(RIGHT_MOTOR_ENB, rightWheelVelocity);

  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  analogWrite(LEFT_MOTOR_ENA, leftWheelVelocity);
}

void left() {
  digitalWrite(RIGHT_MOTOR_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_IN4, HIGH);
  analogWrite(RIGHT_MOTOR_ENB, rightWheelVelocity);

  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  analogWrite(LEFT_MOTOR_ENA, leftWheelVelocity);

}

void stop() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); analogWrite(ENA, 0);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); analogWrite(ENB, 0);
}

void rightPlus(){ rightWheelVelocity < velMax? rightWheelVelocity += 10: rightWheelVelocity = velMax;}
void rightMinus(){ rightWheelVelocity > velMin? rightWheelVelocity -= 10: rightWheelVelocity = velMin;}
void leftPlus(){ leftWheelVelocity < velMax? leftWheelVelocity += 10: leftWheelVelocity = velMax;}
void leftMinus(){ leftWheelVelocity > velMin? leftWheelVelocity -= 10: leftWheelVelocity = velMin;}


