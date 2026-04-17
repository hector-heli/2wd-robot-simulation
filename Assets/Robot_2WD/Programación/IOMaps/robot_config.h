/*
 * CONFIGURACIÓN GENERAL DEL ROBOT 2WD
 * 
 * Archivo centralizado con todos los parámetros de configuración del robot.
 * Incluya este archivo en sus sketches para acceder a todas las constantes.
 * 
 * #include "robot_config.h"
 */

#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

// ============================================================================
// INFORMACIÓN DEL ROBOT
// ============================================================================
#define ROBOT_NAME              "2WD Robot"
#define ROBOT_VERSION           "1.0"
#define LAST_MODIFIED           "2026-03-28"

// ============================================================================
// CONFIGURACIÓN DE COMUNICACIÓN
// ============================================================================
#define SERIAL_BAUD             9600      // Velocidad de comunicación serial
#define BLUETOOTH_BAUD          9600      // Velocidad del módulo Bluetooth HC-06

// ============================================================================
// I/O MAPPINGS - PINES
// ============================================================================

// Encoders (Sensores de velocidad)
#define RIGHT_ENCODER           3
#define LEFT_ENCODER            2

// Sensores IR (Seguidor de línea)
#define RIGHT_IR_SENSOR         A0
#define LEFT_IR_SENSOR          A1

// Sensor Ultrasónico HC-SR04
#define SONAR_TRIGGER_PIN       18
#define SONAR_ECHO_PIN          19

// Motor Driver L298N - Motor Derecho
#define RIGHT_MOTOR_IN3         7         // Control de dirección
#define RIGHT_MOTOR_IN4         8         // Control de dirección
#define RIGHT_MOTOR_ENB         9         // PWM para velocidad

// Motor Driver L298N - Motor Izquierdo
#define LEFT_MOTOR_IN1          4         // Control de dirección
#define LEFT_MOTOR_IN2          6         // Control de dirección
#define LEFT_MOTOR_ENA          5         // PWM para velocidad

// Servo Motor (si se utiliza)
#define SERVO_PIN               12

// Módulo Bluetooth HC-06
#define BT_TX_PIN               10        // TX del Arduino -> RX del HC-06
#define BT_RX_PIN               11        // RX del Arduino <- TX del HC-06

// ============================================================================
// CONFIGURACIÓN DE MOTORES
// ============================================================================

// Velocidades
#define MOTOR_SPEED_MAX         255       // Velocidad máxima (PWM)
#define MOTOR_SPEED_MIN         80        // Velocidad mínima para vencer fricción
#define MOTOR_SPEED_DEFAULT     200       // Velocidad por defecto

// Velocidades iniciales por rueda
#define RIGHT_WHEEL_SPEED_INIT  200
#define LEFT_WHEEL_SPEED_INIT   200

// Parámetro de incremento de velocidad
#define SPEED_STEP              10        // Incremento/decremento por comando

// Tiempos de retraso (milisegundos)
#define MOTOR_DELAY             50        // Delay entre actualizaciones de motor
#define MOTOR_SPIN_DELAY        500       // Delay para giros

// ============================================================================
// CONFIGURACIÓN DE SENSORES IR (LÍNEA)
// ============================================================================

// Umbrales de detección
#define IR_THRESHOLD_WHITE      550       // Umbral para detectar línea blanca
#define IR_SENSOR_READ_DELAY    50        // Delay entre lecturas

// Estados de sensores
#define SENSOR_ON_WHITE         0         // Cuando está sobre la línea
#define SENSOR_ON_BLACK         1         // Cuando no está sobre la línea

// ============================================================================
// CONFIGURACIÓN DEL SENSOR ULTRASÓNICO
// ============================================================================

// Parámetros de medición
#define SONAR_TRIGGER_PULSE     10        // Duración del pulso en microsegundos
#define SONAR_TRIGGER_DELAY     2         // Delay previo en microsegundos
#define SONAR_SOUND_SPEED       0.034     // Velocidad del sonido (cm/microsegundo)
#define SONAR_READ_DELAY        100       // Delay entre lecturas en milisegundos

// Distancias límite
#define SONAR_CRITICAL_DISTANCE 15        // Distancia crítica para evitar obstáculos (cm)
#define SONAR_WARNING_DISTANCE  30        // Distancia de advertencia (cm)
#define SONAR_MAX_DISTANCE      200       // Distancia máxima de medición (cm)

// ============================================================================
// CONFIGURACIÓN DE ENCODERS
// ============================================================================

// Parámetros físicos del robot
#define WHEEL_DIAMETER          6.5       // Diámetro de la rueda en cm
#define WHEEL_CIRCUMFERENCE     20.42     // Circunferencia = π * diámetro
#define PULSES_PER_REVOLUTION   20        // Pulsos del encoder por revolución
#define ROBOT_WHEELBASE         10.0      // Distancia entre ruedas en cm

// Conversión de distancia
#define CM_PER_PULSE            (WHEEL_CIRCUMFERENCE / PULSES_PER_REVOLUTION)

// ============================================================================
// CONFIGURACIÓN DE CONTROL POR BLUETOOTH
// ============================================================================

// Comandos de movimiento
#define CMD_FORWARD             'F'       // Movimiento adelante
#define CMD_BACKWARD            'B'       // Movimiento atrás
#define CMD_LEFT                'L'       // Giro a la izquierda
#define CMD_RIGHT               'R'       // Giro a la derecha
#define CMD_STOP                'S'       // Detener

// Comandos de velocidad
#define CMD_LEFT_SPEED_UP       'T'       // Aumentar velocidad izquierda
#define CMD_LEFT_SPEED_DOWN     'S'       // Disminuir velocidad izquierda
#define CMD_RIGHT_SPEED_UP      'C'       // Aumentar velocidad derecha
#define CMD_RIGHT_SPEED_DOWN    'X'       // Disminuir velocidad derecha

// ============================================================================
// CONFIGURACIÓN DE MODOS DE OPERACIÓN
// ============================================================================

#define MODE_MANUAL             0         // Control manual por Bluetooth
#define MODE_LINE_FOLLOWER      1         // Seguidor automático de línea
#define MODE_OBSTACLE_AVOIDANCE 2         // Evitador automático de obstáculos
#define MODE_TEST               3         // Modo de prueba

// ============================================================================
// CONFIGURACIÓN GENERAL
// ============================================================================

#define DEBUG_MODE              true      // Activa mensajes de debug por serial
#define ENABLE_BLUETOOTH        true      // Activa comunicación Bluetooth
#define ENABLE_ENCODERS         true      // Activa lectura de encoders
#define ENABLE_IR_SENSORS       true      // Activa sensores IR
#define ENABLE_ULTRASONIC       true      // Activa sensor ultrasónico

// ============================================================================
// FUNCIONES DE UTILIDAD
// ============================================================================

// Macros para controlar motores fácilmente
#define constrain_speed(x)      constrain(x, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX)

// ============================================================================
// FUNCIONES DE CONFIGURACIÓN DE PINES I/O
// ============================================================================

/**
 * Configura todos los pines de entrada del robot
 * Incluye: Encoders, sensores IR, sensor ultrasónico
 */
void setupInputPins() {
  if (ENABLE_ENCODERS) {
    pinMode(LEFT_ENCODER, INPUT);
    pinMode(RIGHT_ENCODER, INPUT);
  }
  
  if (ENABLE_IR_SENSORS) {
    pinMode(LEFT_IR_SENSOR, INPUT);
    pinMode(RIGHT_IR_SENSOR, INPUT);
  }
  
  if (ENABLE_ULTRASONIC) {
    pinMode(SONAR_ECHO_PIN, INPUT);
  }
}

/**
 * Configura todos los pines de salida del robot
 * Incluye: Motores, servo, sensor ultrasónico trigger
 */
void setupOutputPins() {
  // Configurar pines del motor izquierdo
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(LEFT_MOTOR_ENA, OUTPUT);
  
  // Configurar pines del motor derecho
  pinMode(RIGHT_MOTOR_IN3, OUTPUT);
  pinMode(RIGHT_MOTOR_IN4, OUTPUT);
  pinMode(RIGHT_MOTOR_ENB, OUTPUT);
  
  // Detener motores inicialmente
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_IN4, LOW);
  analogWrite(LEFT_MOTOR_ENA, 0);
  analogWrite(RIGHT_MOTOR_ENB, 0);
  
  // Configurar servo (si está habilitado)
  pinMode(SERVO_PIN, OUTPUT);
  
  // Configurar trigger del sensor ultrasónico
  if (ENABLE_ULTRASONIC) {
    pinMode(SONAR_TRIGGER_PIN, OUTPUT);
    digitalWrite(SONAR_TRIGGER_PIN, LOW);
  }
}

/**
 * Configura la comunicación serial (depuración)
 */
void setupSerial() {
  Serial.begin(SERIAL_BAUD);
  delay(500);
  
  if (DEBUG_MODE) {
    Serial.println("╔════════════════════════════════════════╗");
    Serial.println("║      ROBOT 2WD - INICIANDO SISTEMA    ║");
    Serial.println("╚════════════════════════════════════════╝");
    Serial.print("Nombre: ");
    Serial.println(ROBOT_NAME);
    Serial.print("Versión: ");
    Serial.println(ROBOT_VERSION);
    Serial.println("═══════════════════════════════════════════");
  }
}

/**
 * Configura la comunicación Bluetooth HC-06
 * Requiere: #include <SoftwareSerial.h>
 * Uso: SoftwareSerial BT = setupBluetooth();
 */
void setupBluetoothPins() {
  if (ENABLE_BLUETOOTH) {
    if (DEBUG_MODE) {
      Serial.println("[INFO] Módulo Bluetooth configurado");
      Serial.print("  TX Pin: ");
      Serial.println(BT_TX_PIN);
      Serial.print("  RX Pin: ");
      Serial.println(BT_RX_PIN);
    }
  }
}

/**
 * Inicializa todos los pines y sistemas del robot
 * Llama esta función desde setup() del sketch
 */
void initializeRobot() {
  setupSerial();
  setupInputPins();
  setupOutputPins();
  setupBluetoothPins();
  
  if (DEBUG_MODE) {
    Serial.println("[✓] Pines I/O inicializados correctamente");
    Serial.println("═══════════════════════════════════════════");
    Serial.println();
  }
}

/**
 * Detiene todos los motores del robot
 */
void stopAllMotors() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_IN4, LOW);
  analogWrite(LEFT_MOTOR_ENA, 0);
  analogWrite(RIGHT_MOTOR_ENB, 0);
}

/**
 * Established velocidad de un motor específico
 * motor: 0 = izquierdo, 1 = derecho
 * speed: 0-255 (PWM)
 */
void setMotorSpeed(uint8_t motor, uint8_t speed) {
  speed = constrain_speed(speed);
  
  if (motor == 0) {  // Motor izquierdo
    analogWrite(LEFT_MOTOR_ENA, speed);
  } else {           // Motor derecho
    analogWrite(RIGHT_MOTOR_ENB, speed);
  }
}

/**
 * Establece la dirección de un motor
 * motor: 0 = izquierdo, 1 = derecho
 * direction: true = adelante, false = atrás
 */
void setMotorDirection(uint8_t motor, boolean forward) {
  if (motor == 0) {  // Motor izquierdo
    digitalWrite(LEFT_MOTOR_IN1, forward ? HIGH : LOW);
    digitalWrite(LEFT_MOTOR_IN2, forward ? LOW : HIGH);
  } else {           // Motor derecho
    digitalWrite(RIGHT_MOTOR_IN3, forward ? LOW : HIGH);
    digitalWrite(RIGHT_MOTOR_IN4, forward ? HIGH : LOW);
  }
}

/**
 * Controla un motor completamente (velocidad + dirección)
 * motor: 0 = izquierdo, 1 = derecho
 * speed: -255 a 255 (negativo = atrás, positivo = adelante)
 */
void controlMotor(uint8_t motor, int16_t speed) {
  boolean forward = (speed >= 0);
  uint8_t pwm = abs(speed);
  
  setMotorDirection(motor, forward);
  setMotorSpeed(motor, pwm);
}

/**
 * Lee el valor de un sensor IR
 * sensor: 0 = izquierdo, 1 = derecho
 * Retorna: valor analógico (0-1023)
 */
uint16_t readIRSensor(uint8_t sensor) {
  if (sensor == 0) {
    return analogRead(LEFT_IR_SENSOR);
  } else {
    return analogRead(RIGHT_IR_SENSOR);
  }
}

/**
 * Detecta si el robot está sobre la línea
 * sensor: 0 = izquierdo, 1 = derecho
 * Retorna: true si está sobre la línea blanca, false si está sobre fondo oscuro
 */
boolean isOnLine(uint8_t sensor) {
  return (readIRSensor(sensor) < IR_THRESHOLD_WHITE);
}

/**
 * Lee la distancia del sensor ultrasónico en centímetros
 * Retorna: distancia en cm (0-200)
 */
float readUltrasonicDistance() {
  // Enviar pulso de trigger
  digitalWrite(SONAR_TRIGGER_PIN, LOW);
  delayMicroseconds(SONAR_TRIGGER_DELAY);
  digitalWrite(SONAR_TRIGGER_PIN, HIGH);
  delayMicroseconds(SONAR_TRIGGER_PULSE);
  digitalWrite(SONAR_TRIGGER_PIN, LOW);
  
  // Medir duración del echo
  long duration = pulseIn(SONAR_ECHO_PIN, HIGH, 30000);
  
  // Calcular distancia
  float distance = (duration * SONAR_SOUND_SPEED) / 2.0;
  
  // Limitar a rango máximo
  if (distance > SONAR_MAX_DISTANCE) {
    distance = SONAR_MAX_DISTANCE;
  }
  
  return distance;
}

/**
 * Verifica si hay un obstáculo crítico
 * Retorna: true si distancia < SONAR_CRITICAL_DISTANCE
 */
boolean hasObstacle() {
  float distance = readUltrasonicDistance();
  return (distance < SONAR_CRITICAL_DISTANCE);
}

/**
 * Imprime el estado actual de todos los componentes (para debug)
 */
void printRobotStatus() {
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║         ESTADO DEL ROBOT 2WD          ║");
  Serial.println("╚════════════════════════════════════════╝");
  
  if (ENABLE_IR_SENSORS) {
    Serial.print("Sensor IR Izquierdo: ");
    Serial.println(readIRSensor(0));
    Serial.print("Sensor IR Derecho:   ");
    Serial.println(readIRSensor(1));
    Serial.print("Sobre línea (Izq): ");
    Serial.println(isOnLine(0) ? "SÍ" : "NO");
    Serial.print("Sobre línea (Der): ");
    Serial.println(isOnLine(1) ? "SÍ" : "NO");
  }
  
  if (ENABLE_ULTRASONIC) {
    Serial.print("Distancia (cm):      ");
    Serial.println(readUltrasonicDistance());
    Serial.print("Obstáculo cercano:   ");
    Serial.println(hasObstacle() ? "SÍ" : "NO");
  }
  
  Serial.println("═══════════════════════════════════════════");
}

#endif // ROBOT_CONFIG_H
