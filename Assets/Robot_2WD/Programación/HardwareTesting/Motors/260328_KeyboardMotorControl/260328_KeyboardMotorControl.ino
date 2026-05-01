/* Keyboard Motor Control  
  ***version 1.0***

    Este código es un programa de control de motores para un robot, que utiliza comandos enviados a través del monitor serial para mover el robot hacia adelante, hacia atrás, girar a la izquierda, girar a la derecha o detenerse. El programa configura los pines de control de los motores y responde a los comandos 'F', 'B', 'L', 'R' y 'S' para controlar el movimiento del robot.
*/

#include <mapping.h>

int leftMotorSpeed = 200; // Velocidad de los motores (0-255)
int rightMotorSpeed = 200; // Velocidad de los motores (0-255)
int maxMotorSpeed = 250; // Velocidad máxima permitida para los motores

void setup() {
  Serial.begin(9600);
  for (int i=4; i<9; i++) pinMode(i, OUTPUT);
  for (int i=4; i<9; i++) digitalWrite(i, LOW);


}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    Serial.print("Comando recibido: "); 
    Serial.print(command);
    Serial.print("   Velocidad izquierda: "); 
    Serial.print(leftMotorSpeed);
    Serial.print("   Velocidad derecha: "); 
    Serial.println(rightMotorSpeed);
    switch (command) {
      case 'F': // Move Forward
        digitalWrite(RIGHT_MOTOR_IN3, LOW);
        digitalWrite(RIGHT_MOTOR_IN4, HIGH);
        digitalWrite(LEFT_MOTOR_IN1, HIGH);
        digitalWrite(LEFT_MOTOR_IN2, LOW);
        analogWrite(RIGHT_MOTOR_ENB, rightMotorSpeed);
        analogWrite(LEFT_MOTOR_ENA, leftMotorSpeed);
        break;
      case 'B': // Move Backward
        digitalWrite(RIGHT_MOTOR_IN3, HIGH);
        digitalWrite(RIGHT_MOTOR_IN4, LOW);
        digitalWrite(LEFT_MOTOR_IN1, LOW);
        digitalWrite(LEFT_MOTOR_IN2, HIGH);
        analogWrite(RIGHT_MOTOR_ENB, rightMotorSpeed);
        analogWrite(LEFT_MOTOR_ENA, leftMotorSpeed);
        break;
      case 'L': // Turn Left
        digitalWrite(RIGHT_MOTOR_IN3, LOW);
        digitalWrite(RIGHT_MOTOR_IN4, HIGH);
        digitalWrite(LEFT_MOTOR_IN1, LOW);
        digitalWrite(LEFT_MOTOR_IN2, LOW);
        analogWrite(RIGHT_MOTOR_ENB, rightMotorSpeed);
        analogWrite(LEFT_MOTOR_ENA, leftMotorSpeed);
        break;
      case 'R': // Turn Right
        digitalWrite(RIGHT_MOTOR_IN3, LOW);
        digitalWrite(RIGHT_MOTOR_IN4, LOW);
        digitalWrite(LEFT_MOTOR_IN1, HIGH);
        digitalWrite(LEFT_MOTOR_IN2, LOW);
        analogWrite(RIGHT_MOTOR_ENB, rightMotorSpeed);
        analogWrite(LEFT_MOTOR_ENA, leftMotorSpeed);
        break;
      case 't': // Left Motor Speed Up
        leftMotorSpeed = min(leftMotorSpeed + 10, maxMotorSpeed);
        break;
      case 's': // Left Motor Speed Down
        leftMotorSpeed = max(leftMotorSpeed - 10, 80);
        break;
      case 'c': // Right Motor Speed Up
        rightMotorSpeed = min(rightMotorSpeed + 10, maxMotorSpeed);
        break;
      case 'x': // Right Motor Speed Down
        rightMotorSpeed = max(rightMotorSpeed - 10, 80);
        break;

      case 'S': // Stop
        for (int i=4; i<9; i++) digitalWrite(i, LOW);
        break;
      default:
        Serial.println("Comando no reconocido. Use F, B, L, R para mover, t/s para ajustar velocidad izquierda, c/x para ajustar velocidad derecha, S para detener.");
    }
  }
}
