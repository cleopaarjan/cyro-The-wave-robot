#include <Servo.h>

Servo myServo;

const int TRIG_PIN  = 9;
const int ECHO_PIN  = 8;
const int SERVO_PIN = 7;

const int DISTANCE_CM = 50; // waves if something within 50cm

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void wave() {
  myServo.write(0);
  delay(200);
  myServo.write(90);
  delay(200);
}

void setup() {
  myServo.attach(SERVO_PIN);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myServo.write(90);
}

void loop() {
  long distance = getDistance();

  if (distance > 0 && distance < DISTANCE_CM) {
    wave(); // keeps waving continuously while something is there
  } else {
    myServo.write(90); // arm rests when nothing detected
  }

  delay(50);
}