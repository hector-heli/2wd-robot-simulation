/*Monitor de Encoders
  Este programa se encarga de monitorear los encoders del robot y mostrar su conteo en el monitor serie. El conteo se actualiza cada vez que hay un cambio en los encoders, lo que permite observar el movimiento del robot en tiempo real. 

	Además, se implementa un filtro de media móvil exponencial (EMA) para suavizar las lecturas de RPM, proporcionando una visualización más estable de la velocidad de las ruedas. El programa también incluye la capacidad de recibir comandos a través del monitor serie para controlar la velocidad de los motores, lo que facilita las pruebas y ajustes durante el desarrollo del robot.

	Autor: Héctor Helí Ruiz García
	Fecha: 2026-05-01
*/

#include <robot_config.h>   

const unsigned long updateInterval = 100; // ms
unsigned long prevMillis = 0;
unsigned long currentMillis;

// Comunicación serial
String serialData = "";
bool serialDataReady = false;
const char serialDelimiter = ','; // Delimitador para separar datos en la cadena serial
const int dataLength = 1; // Longitud máxima de la cadena serial
int data[dataLength]; // Array para almacenar los datos convertidos.
int outValue; // Variable global para almacenar el valor convertido de la cadena serial

const float emaAlpha = 0.2; // Coeficiente EMA: 0.1-0.3 es buena opción
const float PI_VALUE = 3.14159265;
const float RPM_TO_RAD_S = 2.0 * PI_VALUE / 60.0;
float emaRpmR = 0;
float emaRpmL = 0;
bool emaInitialized = false;

void setup() {
	initializeRobot(); // Inicializa pines y comunicación serial
	// controlMotor(0, 255); // Mover motores al iniciar
	// controlMotor(1, 255);

  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), rightEncoder_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), leftEncoder_ISR, CHANGE);
	unsigned long currentMillis = millis();
}

void loop() { 
	bluetoothSerial.listen(); // Asegura que estamos escuchando el puerto Bluetooth
	serialEvent(); // Maneja la lectura de datos seriales
	if(serialDataReady) {
		for(int i = 0; i < dataLength; i++) {
			int commaIndex = serialData.indexOf(serialDelimiter);
			data[i] = serialData.substring(0, commaIndex).toInt();
			serialData = serialData.substring(commaIndex + 1);
		}
		outValue = data[0];
		outValue > 0 ? controlMotor(1, outValue) : controlMotor(1, -outValue);
		serialData = ""; // Limpiar la cadena serial para la próxima lectura
		serialDataReady = false; // Reiniciar bandera
	}
	Serial.println("outValue: "); Serial.println(outValue); // Imprime el valor procesado para depuración

  if (currentMillis - prevMillis >= updateInterval) {
    noInterrupts();
    long rCount = rCountEncoder;
    long lCount = lCountEncoder;
    interrupts();

    long deltaR = rCount - rCountEncoderPrev;
    long deltaL = lCount - lCountEncoderPrev;
    float intervalSeconds = updateInterval / 1000.0;
    float rpmR = (deltaR * 60.0) / (ENCODER_PPR * intervalSeconds);
    float rpmL = (deltaL * 60.0) / (ENCODER_PPR * intervalSeconds);
    float omegaR = rpmR * RPM_TO_RAD_S;
    float omegaL = rpmL * RPM_TO_RAD_S;

		Serial.print(">");
    Serial.print("izquierdo:");	Serial.print(lCount);
		Serial.print(",");
    Serial.print("RPM_izquierdo:"); Serial.print(rpmL, 1);
		Serial.print(",");
    Serial.print("rad_s_izquierdo:"); Serial.print(omegaL, 2);
		Serial.print(",");
    Serial.print("derecho: "); Serial.print(rCount);
		Serial.print(",");
    Serial.print("RPM_derecho: "); Serial.print(rpmR, 1);
		Serial.print(",");
    Serial.print("rad_s_derecho:"); Serial.print(omegaR, 2);
		Serial.print(",");

    rCountEncoderPrev = rCount;
    lCountEncoderPrev = lCount;
    prevMillis = currentMillis;

    if (!emaInitialized) {
      emaRpmR = rpmR;
      emaRpmL = rpmL;
      emaInitialized = true;
    } else {
      emaRpmR = emaAlpha * rpmR + (1.0 - emaAlpha) * emaRpmR;
      emaRpmL = emaAlpha * rpmL + (1.0 - emaAlpha) * emaRpmL;
    }

    Serial.print("RPM_derecho_filtrado:"); Serial.print(emaRpmR, 1);
    Serial.print(",");
    Serial.print("RPM_izquierdo_filtrado:"); Serial.println(emaRpmL, 1);
    Serial.println();
  }
}

void serialEvent() {
	while (bluetoothSerial.available()>0) {
		char incomingByte = (char)bluetoothSerial.read();
		serialData += incomingByte;
		if (incomingByte == '\n') { // Fin de línea o longitud máxima alcanzada
			serialDataReady = true;
			break; // Salir del bucle para procesar los datos
		}
	}
}

