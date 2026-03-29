#include <robot_config.h>

void robotMotionControl(uint8_t command) {
  // Aquí puedes agregar funciones para controlar el movimiento del robot
  // utilizando las funciones definidas en robot_config.h
  switch (command) {
      case CMD_FORWARD: // Move Forward
        controlMotor(0, RIGHT_WHEEL_SPEED_INIT);
        controlMotor(1, LEFT_WHEEL_SPEED_INIT);
        break;
      case CMD_BACKWARD: // Move Backward
        controlMotor(0, -RIGHT_WHEEL_SPEED_INIT);
        controlMotor(1, -LEFT_WHEEL_SPEED_INIT);
        break;
      case CMD_LEFT: // Turn Left
        controlMotor(0, 0 );
        controlMotor(1, LEFT_WHEEL_SPEED_INIT);
        break;
      case CMD_RIGHT: // Turn Right
        controlMotor(0, RIGHT_WHEEL_SPEED_INIT);
        controlMotor(1, 0);
        break;
      case CMD_STOP: // Stop
        stopAllMotors();
      break;
      default:
        Serial.println("Unknown command");
    }
}