#include <Arduino.h>
#include <mapping.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <PID_v1.h>


// SoftwareSerial BT(Serial_RX_PIN, Serial_TX_PIN);  // RX, TX para Bluetooth
NewPing sonar(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, MAX_DISTANCE);
Servo servo;




//PID de los motores

double Setpoint_R=0, Input_R=0, Output_R=0;
double Setpoint_L=0, Input_L=0, Output_L=0;

double Kp_R=0.5, Ki_R=0, Kd_R=0;
double Kp_L=0.5, Ki_L=0, Kd_L=0;

PID pidR(&Input_R, &Output_R, &Setpoint_R, Kp_R, Ki_R, Kd_R, DIRECT);
PID pidL(&Input_L, &Output_L, &Setpoint_L, Kp_L, Ki_L, Kd_L, DIRECT);



// Variables usadas en ISR deben ser volatile
volatile long encoderCounts[2] = {0, 0};
short speeds[2] = {0, 0};
float rpm[2] = {0.0, 0.0};
short angle = 0;
bool flag = false;

// Variables para el filtro de Media Móvil
const int WINDOW_SIZE = 9;
short history_L[WINDOW_SIZE];
short history_R[WINDOW_SIZE];
int history_idx = 0;
short raw_speeds[2] = {0, 0}; // Para guardar la lectura directa de Serial

// ISR optimizadas
void ISR_left() {
  if (speeds[0] >= 0) encoderCounts[0]++;
  else if (speeds[0] < 0) encoderCounts[0]--;
}

void ISR_right() {
  if (speeds[1] >= 0) encoderCounts[1]++;
  else if (speeds[1] < 0) encoderCounts[1]--;
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);

  // BT.begin(9600);
  // BT.setTimeout(10);

  // servo.attach(SERVO_PIN);
  
  // Ajuste de límites para permitir retroceso
  pidR.SetOutputLimits(-255, 255);
  pidL.SetOutputLimits(-255, 255);

  pidR.SetMode(AUTOMATIC);
  pidL.SetMode(AUTOMATIC);

  // Inicializar buffers del filtro en 0
  for(int i = 0; i < WINDOW_SIZE; i++) {
    history_L[i] = 0;
    history_R[i] = 0;
  }

  // Configurar pines de motores
  pinMode(LEFT_MOTOR_IN1, OUTPUT); pinMode(LEFT_MOTOR_IN2, OUTPUT); pinMode(LEFT_MOTOR_ENA, OUTPUT);
  pinMode(RIGHT_MOTOR_IN3, OUTPUT); pinMode(RIGHT_MOTOR_IN4, OUTPUT); pinMode(RIGHT_MOTOR_ENB, OUTPUT);

  // Interrupciones (Pines 2 y 3 usualmente en Nano)
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), ISR_left, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), ISR_right, CHANGE);
}

void calculateRPM() {

  noInterrupts();
  long countsL = encoderCounts[0];
  long countsR = encoderCounts[1];
  encoderCounts[0] = 0;
  encoderCounts[1] = 0;
  interrupts();

  // El signo se mantiene automáticamente porque los ISR ya suman o restan
  rpm[0] = ((float)countsL / (float)ENCODER_PPR) * 600.0; 
  rpm[1] = ((float)countsR / (float)ENCODER_PPR) * 600.0;

  // ENVIAR SOLO AQUÍ para no saturar a Python
  Serial.print(rpm[0]);
  Serial.print(",");
  Serial.print(rpm[1]);

}

void readIR(){
  Serial.print(",");
  Serial.print(digitalRead(LEFT_IR_SENSOR));
  Serial.print(",");
  Serial.print(digitalRead(RIGHT_IR_SENSOR));
}

void readSonar(){
  Serial.print(",");
  Serial.print(sonar.ping_cm());
}

void moveMotors(short leftSpeed, short rightSpeed) {
  // Lógica de motor izquierdo
  if(leftSpeed > 0) {
    digitalWrite(LEFT_MOTOR_IN1, LOW); digitalWrite(LEFT_MOTOR_IN2, HIGH);
    analogWrite(LEFT_MOTOR_ENA, leftSpeed);
  } else if (leftSpeed < 0) {
    digitalWrite(LEFT_MOTOR_IN1, HIGH); digitalWrite(LEFT_MOTOR_IN2, LOW);
    analogWrite(LEFT_MOTOR_ENA, -leftSpeed);
  } else {
    digitalWrite(LEFT_MOTOR_IN1, LOW); digitalWrite(LEFT_MOTOR_IN2, LOW);
    analogWrite(LEFT_MOTOR_ENA, 0);
  }

  // Lógica de motor derecho
  if(rightSpeed > 0) {
    digitalWrite(RIGHT_MOTOR_IN3, HIGH); digitalWrite(RIGHT_MOTOR_IN4, LOW);
    analogWrite(RIGHT_MOTOR_ENB, rightSpeed);
  } else if (rightSpeed < 0) {
    digitalWrite(RIGHT_MOTOR_IN3, LOW); digitalWrite(RIGHT_MOTOR_IN4, HIGH);
    analogWrite(RIGHT_MOTOR_ENB, -rightSpeed);
  } else {
    digitalWrite(RIGHT_MOTOR_IN3, LOW); digitalWrite(RIGHT_MOTOR_IN4, LOW);
    analogWrite(RIGHT_MOTOR_ENB, 0);
  }
}


void loop() {
  // Leer comandos de Python (Hardware Serial)
  if (Serial.available() > 0) {
    raw_speeds[0] = Serial.parseInt();
    raw_speeds[1] = Serial.parseInt();
    // Limpiar basura (\n)
    while(Serial.available() > 0) Serial.read();
  }


  static unsigned long timePrevious = 0;
  unsigned long timeCurrent = millis();
  const int ts = 100; // 100ms
  short ts_out = 0;



  if (timeCurrent - timePrevious >= ts) {
    ts_out = timeCurrent - timePrevious;

    // Actualizar el filtro de media móvil con las últimas velocidades deseadas
    history_L[history_idx] = raw_speeds[0];
    history_R[history_idx] = raw_speeds[1];
    history_idx = (history_idx + 1) % WINDOW_SIZE;

    long sum_L = 0;
    long sum_R = 0;
    for(int i = 0; i < WINDOW_SIZE; i++) {
      sum_L += history_L[i];
      sum_R += history_R[i];
    }
    
    // Las velocidades "speeds" ahora son el promedio (filtradas)
    speeds[0] = sum_L / WINDOW_SIZE;
    speeds[1] = sum_R / WINDOW_SIZE;

    // servo.write(angle);
    // if(angle >= 180) flag = true;
    // if(angle <= 0) flag = false;

    // if(flag == false) angle +=5;
    // if(flag == true) angle -=5;

    // Actualizamos RPM primero para que el PID tenga el dato más reciente
    calculateRPM();
    readIR();
    readSonar();
    Serial.print(","); Serial.println(ts_out);

    // Mapeo correcto de Inputs y Setpoints
    Input_L = rpm[0];
    Input_R = rpm[1];

    Setpoint_L = (double)speeds[0]; // Usamos la velocidad filtrada
    Setpoint_R = (double)speeds[1];

    // Cálculo del PID
    pidL.Compute();
    pidR.Compute();

    // Enviar las salidas del PID a los motores
    moveMotors(Output_L, Output_R);

    timePrevious = timeCurrent;
  }
}