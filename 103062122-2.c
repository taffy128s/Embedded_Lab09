#include <Arduino_FreeRTOS.h>
#include <Stepper.h>
#define STEPS 2048

const int trigPin = 13;
const int echoPin = 12;
long duration;
int distance;
Stepper stepper(STEPS, 8, 10, 9, 11);
double previous;
int stat;

void lightTask(void *pvParameters);
void distanceTask(void *pvParameters);
void moveTask(void *pvParameters);

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(10);
  previous = 0;
  stat = 0;
  pinMode(A0, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  xTaskCreate(lightTask, (const portCHAR *) "light", 128, NULL, 1, NULL);
  xTaskCreate(distanceTask, (const portCHAR *) "distance", 128, NULL, 1, NULL);
  xTaskCreate(moveTask, (const portCHAR *) "move", 128, NULL, 1, NULL);
}

void loop() {
  
}

void lightTask(void *pvParameters) {
  while (1) {
    Serial.println(stat);
    int pr = analogRead(A0);
    Serial.print("pr: ");
    Serial.println(pr);
    if (pr < 800) stat = 2;
    delay(500);
  }
}

void distanceTask(void *pvParameters) {
  while (1) {
    Serial.println(stat);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("distance: ");
    Serial.println(distance);
    if (distance > 5) stat = 3;
    delay(300);
  }
}

void moveTask(void *pvParameters) {
  while (1) {
    if (stat == 2) {
      if (previous <= 400) {
        stepper.step(50);
        previous += 50;
      }
    } else if (stat == 3) {
      if (previous >= 50) {
        stepper.step(-50);
        previous -= 50;
      }
    }
  }
}

