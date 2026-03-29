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

void setup() {
  Serial.begin(9600);  // Debug
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
      case 'T': leftPlus(); break;
      case 'X': rightMinus(); break;
      case 'S': leftMinus(); break;
      case 'C': rightPlus(); break;
      default: stop();
    }
    Serial.print(">");
    Serial.print("Vel Izq: ");
    Serial.print(leftWheelVelocity);
    Serial.print(",");
    Serial.print("    Vel Der: ");
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

