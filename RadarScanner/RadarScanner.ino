// HC-SR04 Distance Measurement
// Project: Embedded Ultrasonic Radar

const int trigPin = 9;
const int echoPin = 10;

long duration;
float distance;

void setup()
{
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("=== Embedded Ultrasonic Radar ===");
  Serial.println("Distance Measurement Started");
}

void loop()
{
  // Ensure TRIG starts LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10 µs pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo time
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance (cm)
  distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}