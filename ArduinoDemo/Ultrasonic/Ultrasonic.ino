const int TrigPin = A2;
const int EchoPin = A3;
float distance, duration;
void setup() {
	Serial.begin(9600);
	pinMode(TrigPin, OUTPUT);
	pinMode(EchoPin, INPUT);
	Serial.println("Ultrasonic sensor:");
}
void loop() {
	digitalWrite(TrigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(TrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin, LOW);
 
  // Measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(EchoPin, HIGH);
  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance = (duration / 2) * 0.0343;
  
	Serial.print("distance is :");
	Serial.print(distance);
	Serial.print("cm");
	Serial.println();
	delay(1000);
}
