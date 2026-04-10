#include <Arduino.h>
#include <mapping.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX


short velocidades[2] = {0,0};

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  mySerial.begin(9600);
  mySerial.setTimeout(10);
}


void moveMotors(short leftSpeed, short rightSpeed) {
    if(leftSpeed > 0) {
        digitalWrite(LEFT_MOTOR_IN1, HIGH);
        digitalWrite(LEFT_MOTOR_IN2, LOW);
        analogWrite(LEFT_MOTOR_ENA, leftSpeed);
    } else if (leftSpeed < 0) {
        digitalWrite(LEFT_MOTOR_IN1, LOW);
        digitalWrite(LEFT_MOTOR_IN2, HIGH);
        analogWrite(LEFT_MOTOR_ENA, -leftSpeed);
    } else {
        digitalWrite(LEFT_MOTOR_IN1, LOW);
        digitalWrite(LEFT_MOTOR_IN2, LOW);
        analogWrite(LEFT_MOTOR_ENA, 0);
    }

    if(rightSpeed > 0) {
        digitalWrite(RIGHT_MOTOR_IN3, HIGH);
        digitalWrite(RIGHT_MOTOR_IN4, LOW);
        analogWrite(RIGHT_MOTOR_ENB, rightSpeed);
    } else if (rightSpeed < 0) {
        digitalWrite(RIGHT_MOTOR_IN3, LOW);
        digitalWrite(RIGHT_MOTOR_IN4, HIGH);
        analogWrite(RIGHT_MOTOR_ENB, -rightSpeed);
    } else {
        digitalWrite(RIGHT_MOTOR_IN3, LOW);
        digitalWrite(RIGHT_MOTOR_IN4, LOW);
        analogWrite(RIGHT_MOTOR_ENB, 0);
    }
}

void loop() {
  if (Serial.available()){
    for(int i = 0; i < 2; i++) {
      velocidades[i] = Serial.parseInt();
    }
    Serial.print(velocidades[0]);
    Serial.print(",");
    Serial.println(velocidades[1]);
  }

  moveMotors(velocidades[0],velocidades[1]);
}