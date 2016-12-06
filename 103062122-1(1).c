const int trigPin = 13;
const int echoPin = 12;
const int soundDigitalPin = 8;
const int soundAnalogPin = A1;
const int redPin = 11, greenPin = 10, bluePin = 9;

long duration;
int distance;
int soundDigitalVal, soundAnalogVal;
int timecount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(soundDigitalPin, INPUT);
  pinMode(soundAnalogPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  //sound 400
  //light 1000
  //distance 2500

  delay(100);
  timecount++;
  if (timecount == 100) timecount = 0;
  
  if (timecount % 4 == 0) {
    soundAnalogVal = analogRead(soundAnalogPin);
    Serial.print("sound: ");
    Serial.println(soundAnalogVal);
    analogWrite(greenPin, soundAnalogVal);
  }
  if (timecount % 10 == 0) {
    int pr = analogRead(A0);
    Serial.print("pr: ");
    Serial.println(pr);
    double x = (double) pr;
    x = x / 1024 * 256;
    analogWrite(redPin, x);
  }
  if (timecount % 25 == 0) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("distance: ");
    Serial.println(distance);
    analogWrite(bluePin, distance);
  }
  //soundDigitalVal = digitalRead(soundDigitalPin);
  //if (soundDigitalVal == HIGH) Serial.println("HIGH");
  //else Serial.println("LOW");
}
