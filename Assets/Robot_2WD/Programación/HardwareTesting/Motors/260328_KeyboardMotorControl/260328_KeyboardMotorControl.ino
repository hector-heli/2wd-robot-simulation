/* Keyboard Motor Control  
***version 1.0***

Este código es un programa de control de motores para un robot, que utiliza comandos enviados a través del monitor serial para mover el robot hacia adelante, hacia atrás, girar a la izquierda, girar a la derecha o detenerse. El programa configura los pines de control de los motores y responde a los comandos 'F', 'B', 'L', 'R' y 'S' para controlar el movimiento del robot.

*/

#include <mapping.h>

void setup() {
  Serial.begin(9600);
  for (int i=4; i<9; i++) pinMode(i, OUTPUT);
  for (int i=4; i<9; i++) digitalWrite(i, LOW);

    }

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    Serial.print("Received command: "); 
    Serial.println(command);
    switch (command) {
      case 'F': // Move Forward
        digitalWrite(RIGHT_MOTOR_IN3, LOW);
        digitalWrite(RIGHT_MOTOR_IN4, HIGH);
        digitalWrite(LEFT_MOTOR_IN1, HIGH);
        digitalWrite(LEFT_MOTOR_IN2, LOW);
        analogWrite(RIGHT_MOTOR_ENB, 200);
        analogWrite(LEFT_MOTOR_ENA, 200);

        break;
      case 'B': // Move Backward
        digitalWrite(RIGHT_MOTOR_IN3, HIGH);
        digitalWrite(RIGHT_MOTOR_IN4, LOW);
        digitalWrite(LEFT_MOTOR_IN1, LOW);
        digitalWrite(LEFT_MOTOR_IN2, HIGH);
        break;
      case 'L': // Turn Left
        digitalWrite(RIGHT_MOTOR_IN3, LOW);
        digitalWrite(RIGHT_MOTOR_IN4, HIGH);
        digitalWrite(LEFT_MOTOR_IN1, LOW);
        digitalWrite(LEFT_MOTOR_IN2, LOW);
        break;
      case 'R': // Turn Right
        digitalWrite(RIGHT_MOTOR_IN3, LOW);
        digitalWrite(RIGHT_MOTOR_IN4, LOW);
        digitalWrite(LEFT_MOTOR_IN1, HIGH);
        digitalWrite(LEFT_MOTOR_IN2, LOW);
        break;
      case 'S': // Stop
        for (int i=4; i<9; i++) digitalWrite(i, LOW);
        break;
      default:
        Serial.println("Unknown command");
    }
    /* code */
  }
  
 }