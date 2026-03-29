void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  for (int i=4; i<9; i++) pinMode(i, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
 }

void loop() {
  int estado = digitalRead(A0) + digitalRead(A1)*2;
  Serial.print(digitalRead(A0));
  Serial.print("\t\t");
  Serial.println(digitalRead(A1));
  delay(50);

  switch (estado) {
    case 0:
      digitalWrite(5, !HIGH);
      digitalWrite(9, !HIGH);
      break;
    case 1:
      digitalWrite(5, LOW);
      digitalWrite(9, HIGH);
      break;
    case 2:
      digitalWrite(5, HIGH);
      digitalWrite(9, LOW);
      break;
    case 3:
      digitalWrite(5, !LOW);
      digitalWrite(9, !LOW);
      break;

  }


}
