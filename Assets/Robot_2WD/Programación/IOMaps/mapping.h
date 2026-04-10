/* I/O Mappings 

Copie este archivo y péguelo en la carpeta ../Documents/Arduino/libraries/IOMaps para incluirlo en su proyecto de Arduino.


    ENCODERS:
        - Right Encoder: Pin 3
        - Left Encoder: Pin 2
        - Pulses Per Revolution: 40
*/

#define     RIGHT_ENCODER   3
#define     LEFT_ENCODER    2 
#define     ENCODER_PPR     40 
/*
    IR SENSORS:
        - Right IR Sensor: Pin A0
        - Left IR Sensor: Pin A1
*/

#define     RIGHT_IR_SENSOR A0
#define     LEFT_IR_SENSOR  A1

/*
    ULTRASONIC SENSOR:
        - Trigger Pin: Pin 18
        - Echo Pin: Pin 19
        - Max Distance: 200 cm
*/

#define     SONAR_TRIGGER_PIN  18
#define     SONAR_ECHO_PIN     19
#define     MAX_DISTANCE       200

/*
    MOTOR DRIVER:
        - Right Motor: IN3 (Pin 6), IN4 (Pin 4), EN2 (Pin 5)
        - Left Motor: IN1 (Pin 8), IN2 (Pin 7), EN1 (Pin 9)
*/

#define     LEFT_MOTOR_IN1  6
#define     LEFT_MOTOR_IN2  4
#define     LEFT_MOTOR_ENA  5

#define     RIGHT_MOTOR_IN3   8
#define     RIGHT_MOTOR_IN4   7
#define     RIGHT_MOTOR_ENB   9

#define     SERVO_PIN       12

#define     MAX_PWM         255

/*
    BLUETOOTH MODULE:
        - TX Pin: Pin 10
        - RX Pin: Pin 11
*/

#define     BT_TX_PIN        10
#define     BT_RX_PIN        11

