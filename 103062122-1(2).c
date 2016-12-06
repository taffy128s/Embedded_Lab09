#include <Arduino_FreeRTOS.h>

const int trigPin = 13;
const int echoPin = 12;
const int soundDigitalPin = 8;
const int soundAnalogPin = A1;
const int redPin = 11, greenPin = 10, bluePin = 9;

long duration;
int distance;
int soundDigitalVal, soundAnalogVal;
int timecount = 0;

void soundTask(void *pvParameters);
void lightTask(void *pvParameters);
void distanceTask(void *pvParameters);

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
  xTaskCreate(soundTask, (const portCHAR *) "sound", 128, NULL, 1, NULL);
  xTaskCreate(lightTask, (const portCHAR *) "light", 128, NULL, 1, NULL);
  xTaskCreate(distanceTask, (const portCHAR *) "distance", 128, NULL, 1, NULL);
}

void loop() {
    
}

void soundTask(void *pvParameters) {
  while (1) {
    soundAnalogVal = analogRead(soundAnalogPin);
    Serial.print("sound: ");
    Serial.println(soundAnalogVal);
    analogWrite(greenPin, soundAnalogVal);
    delay(400);
  }
}

void lightTask(void *pvParameters) {
  while (1) {
    int pr = analogRead(A0);
    Serial.print("pr: ");
    Serial.println(pr);
    double x = (double) pr;
    x = x / 1024 * 256;
    analogWrite(redPin, x);
    delay(1000);
  }
}

void distanceTask(void *pvParameters) {
  while (1) {
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
    delay(2500);
  }
}
