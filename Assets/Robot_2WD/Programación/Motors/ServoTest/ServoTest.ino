/* ServoTest.ino - Test code for the Servo library
  
Este código es un ejemplo de cómo usar la biblioteca Servo para controlar un servo motor. El programa mueve el servo de 0 a 180 grados y luego de vuelta a 0 grados, imprimiendo la posición del servo en el monitor serial.

Con el fin de que los datos se visualicen gráficamente en la extensión de VSCode SerialPlotter, los datos están formateados de la siguiente manera:
    >Servo Position: X
donde X es el ángulo actual del servo.

*/

#include <mapping.h>
#include <Servo.h>

int time = 25;

Servo servo;
void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
}

void loop() {
  for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.print(">");
    Serial.print("Servo Position: ");
    Serial.print(pos);
    Serial.println();
    delay(time);                       // waits  for the servo to reach the position
  }
  for (int pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.print(">");
    Serial.print("Servo Position: ");
    Serial.print(pos);
    Serial.println();
    delay(time);                       // waits for the servo to reach the position
  }
}
