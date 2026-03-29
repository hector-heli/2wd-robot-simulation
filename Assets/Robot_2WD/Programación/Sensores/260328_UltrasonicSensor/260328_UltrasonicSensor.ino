#include <mapping.h>
// Definimos los pines a los que conectamos el sensor
const int pinTrig = SONAR_TRIGGER_PIN;
const int pinEcho = SONAR_ECHO_PIN;

// Variables para guardar los cálculos
long duracion;
float distancia;

void setup() {
  // Iniciamos la comunicación con la computadora a 9600 baudios
  Serial.begin(9600);
  
  // Configuramos los pines
  pinMode(pinTrig, OUTPUT); // El Trigger EMITE la señal
  pinMode(pinEcho, INPUT);  // El Echo RECIBE la señal
}

void loop() {
  // 1. Asegurarnos de que el Trigger esté apagado por 2 microsegundos
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  
  // 2. Encender el Trigger por 10 microsegundos para enviar el pulso ultrasónico
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  // 3. Medir cuánto tiempo tarda en volver el pulso (en microsegundos)
  duracion = pulseIn(pinEcho, HIGH);
  
  // 4. Calcular la distancia en centímetros
  // La velocidad del sonido es de 0.034 cm/microsegundo.
  // Dividimos entre 2 porque el pulso va y vuelve (hace el doble del recorrido).
  distancia = duracion * 0.034 / 2;
  
  // 5. Imprimir el resultado en el Monitor Serie
  Serial.print(">");
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println("");
  
  // Pausa corta antes de la siguiente medición
  delay(100);
}

