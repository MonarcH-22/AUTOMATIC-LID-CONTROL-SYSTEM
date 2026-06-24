#include <Servo.h>

Servo myServo;

const int trigPin = 7;
const int echoPin = 8;

bool lidOpen = false;
unsigned long lastSeenTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(9);
  myServo.write(0); // Closed position
}

void loop() {

  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Object detected
  if (distance < 20) {

    lastSeenTime = millis();

    if (!lidOpen) {
      myServo.write(90);   // Open
      lidOpen = true;
    }
  }

  // Close 0.5 seconds after object leaves
  if (lidOpen && (millis() - lastSeenTime > 500)) {
    myServo.write(0);      // Close
    lidOpen = false;
  }

  delay(100);
}