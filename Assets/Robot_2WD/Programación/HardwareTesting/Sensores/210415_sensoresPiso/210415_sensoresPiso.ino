/* MONITOREO DE SENSORES DE PISO
 * 
 * El robot tiene dos sensores de piso, uno a la derecha y otro a la izquierda. Estos sensores detectan si el robot está sobre una superficie clara o sobre una línea oscura. El programa lee el estado de ambos sensores y controla los motores del robot en consecuencia:
 * - Si ambos sensores detectan superficie clara (estado 0), el robot se detiene.
 * - Si el sensor derecho detecta línea oscura y el izquierdo detecta superficie clara (estado 1), el robot gira a la derecha.
 * - Si el sensor izquierdo detecta línea oscura y el derecho detecta superficie clara (estado 2), el robot gira a la izquierda.
 * - Si ambos sensores detectan línea oscura (estado 3), el robot avanza hacia adelante.

*/

#include <mapping.h>

void setup() {
  Serial.begin(9600);
  pinMode(RIGHT_IR_SENSOR, INPUT);
  pinMode(LEFT_IR_SENSOR, INPUT);
  pinMode(RIGHT_ENCODER, INPUT);
  pinMode(LEFT_ENCODER, INPUT);

  for (int i=4; i<9; i++) pinMode(i, OUTPUT);
  for (int i=4; i<9; i++) digitalWrite(i, LOW);
 }

void loop() {
  int estado = digitalRead(RIGHT_IR_SENSOR) + digitalRead(LEFT_IR_SENSOR)*2;
  Serial.print(digitalRead(RIGHT_IR_SENSOR));
  Serial.print("\t\t");
  Serial.println(digitalRead(LEFT_IR_SENSOR));
  delay(50);

  switch (estado) {
    case 0:
      digitalWrite(RIGHT_MOTOR_ENB, !HIGH);
      digitalWrite(LEFT_MOTOR_ENA, !HIGH);
      break;
    case 1:
      digitalWrite(RIGHT_MOTOR_ENB, LOW);
      digitalWrite(LEFT_MOTOR_ENA, HIGH);
      break;
    case 2:
      digitalWrite(RIGHT_MOTOR_ENB, HIGH);
      digitalWrite(LEFT_MOTOR_ENA, LOW);
      break;
    case 3:
      digitalWrite(RIGHT_MOTOR_ENB, !LOW);
      digitalWrite(LEFT_MOTOR_ENA, !LOW);
      break;

  }


}
