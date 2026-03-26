#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);  // RX=11, TX=10 para HC-06

// Pines L298N Motores Izquierdos
int IN1 = 7;
int IN2 = 8;
int ENA = 9;  // PWM

// Pines L298N Motores Derechos
int IN3 = 4;
int IN4 = 6;
int ENB = 5; // PWM

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
    Serial.print("Vel Izq: ");
    Serial.print(leftWheelVelocity);
    Serial.print("    Vel Der: ");
    Serial.println(rightWheelVelocity);
  }
}

void front() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, rightWheelVelocity);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, leftWheelVelocity);
}

void back() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, rightWheelVelocity);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, leftWheelVelocity);
}

void right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, rightWheelVelocity);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, leftWheelVelocity);
}

void left() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, rightWheelVelocity);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, leftWheelVelocity);
}

void stop() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); analogWrite(ENA, 0);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); analogWrite(ENB, 0);
}

void rightPlus(){ rightWheelVelocity < velMax? rightWheelVelocity += 10: rightWheelVelocity = velMax;}
void rightMinus(){ rightWheelVelocity > velMin? rightWheelVelocity -= 10: rightWheelVelocity = velMin;}
void leftPlus(){ leftWheelVelocity < velMax? leftWheelVelocity += 10: leftWheelVelocity = velMax;}
void leftMinus(){ leftWheelVelocity > velMin? leftWheelVelocity -= 10: leftWheelVelocity = velMin;}

