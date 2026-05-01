/* Keyboard Motor Control  
***version 1.0***

Este código es un programa de control de motores para un robot, que utiliza comandos enviados a través del monitor serial para mover el robot hacia adelante, hacia atrás, girar a la izquierda, girar a la derecha o detenerse. El programa configura los pines de control de los motores y responde a los comandos 'F', 'B', 'L', 'R' y 'S' para controlar el movimiento del robot.

*/
#include <robot_motion_control.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(BT_TX_PIN, BT_RX_PIN);  // RX=11, TX=10 para HC-06


void setup() {
  BT.begin(BLUETOOTH_BAUD);
  initializeRobot();
  printRobotStatus();
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    Serial.print("Comando Serial Recibido: "); 
    Serial.println(command);

    robotMotionControl(command);
  }

  if (BT.available() > 0) {
    command = BT.read();
    Serial.print("Comando Bluetooth Recibido: "); 
    Serial.println(command);

    robotMotionControl(command);
  } 
  printEncoderCounts();  
 }