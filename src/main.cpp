#include <Arduino.h>
#include <PS4Controller.h>
int ENA;
int IN1;
int IN2;
int ENB;
int IN3;
int IN4;
int speed;

void setup() {
    Serial.begin(115200);
    PS4.begin();
}

void drive(int actualSpeed) {
    PS4.setLed(0, 255, 0);
    PS4.sendToController();
    analogWrite(ENA, actualSpeed);
    analogWrite(ENB, actualSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void reverse(int actualSpeed) {
    PS4.setLed(255, 0, 0);
    PS4.sendToController();
    analogWrite(ENA, actualSpeed);
    analogWrite(ENB, actualSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stop() {
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void move(int speed, int actualSpeed) {
    if (speed > 0) {
        drive(actualSpeed);
    }
    else if (speed<0) {
        reverse(actualSpeed);
    }
    else if (speed == 0) {
        stop();
    }
    else {
        stop();
    }
}

void loop() {
    speed = PS4.LStickY();
    int actualSpeed = map(speed, -255, 0, 255, 1023);

    if (PS4.isConnected()) {
        Serial.print("Connected");
        PS4.setLed(100, 25, 255);
        PS4.sendToController();
        move(speed, actualSpeed);
    } else {
        Serial.print("Fail");
    }
}