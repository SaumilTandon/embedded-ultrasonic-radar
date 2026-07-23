#include <Servo.h>

Servo radarServo;

const int servoPin = 3;
const int trigPin = 9;
const int echoPin = 10;

long duration;
float distance;

float getDistance()
{
  // Clear TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10 us pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read ECHO
  duration = pulseIn(echoPin, HIGH, 30000);

  // No echo received
  if (duration == 0)
    return -1;

  // Convert to cm
  return duration * 0.0343 / 2;
}

void setup()
{
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  radarServo.attach(servoPin);

  radarServo.write(0);
  delay(1000);
}

void loop()
{
  // Sweep 0° -> 180°
  for (int angle = 0; angle <= 180; angle += 2)
  {
    radarServo.write(angle);
    delay(100);

    distance = getDistance();

    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("°");

    Serial.print("    Distance: ");

    if (distance == -1)
      Serial.print("Out of Range");
    else
    {
      Serial.print(distance);
      Serial.print(" cm");
    }

    Serial.println();
  }

  // Sweep 180° -> 0°
  for (int angle = 180; angle >= 0; angle -= 2)
  {
    radarServo.write(angle);
    delay(100);

    distance = getDistance();

    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("°");

    Serial.print("    Distance: ");

    if (distance == -1)
      Serial.print("Out of Range");
    else
    {
      Serial.print(distance);
      Serial.print(" cm");
    }

    Serial.println();
  }
}