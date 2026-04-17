#define BUTTON_PIN 2
volatile unsigned long pulseInTimeBegin = micros();
volatile unsigned long pulseInTimeEnd = micros();
volatile bool newPulseDurationAvailable = false;
void buttonPinInterrupt()
{
  if (digitalRead(BUTTON_PIN) == HIGH) {
    // start measuring
    pulseInTimeBegin = micros();
  }
  else {
    // stop measuring
    pulseInTimeEnd = micros();
    newPulseDurationAvailable = true;
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),
                  buttonPinInterrupt,
                  CHANGE);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);

}
void loop() {
  if (newPulseDurationAvailable) {
    newPulseDurationAvailable = false;
    unsigned long pulseDuration = pulseInTimeEnd - pulseInTimeBegin;
    float rpm = 60000.0/pulseDuration;
    Serial.println(rpm);
  }
  // do your other stuff here
}