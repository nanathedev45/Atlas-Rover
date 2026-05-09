#include <Arduino.h>
#include <PS4Controller.h>
#include <Servo.h>
int ENA;
int IN1;
int IN2;
int ENB;
int IN3;
int IN4;
int speed;
int actualSpeed;
int steering;
int deg;
int steerPin;
Servo steerServo;

void setup() {
    Serial.begin(115200);
    PS4.begin();
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    steerServo.attach(steerPin);
    if (PS4.isConnected()) {
        Serial.println("Connected");
    }
}

void drive(int actualSpeed) {
    //Serial.println("Drive mode");
    analogWrite(ENA, actualSpeed);
    analogWrite(ENB, actualSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void reverse(int actualSpeed) {
    Serial.println("Reverse mode");
    analogWrite(ENA, actualSpeed);
    analogWrite(ENB, actualSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stop() {
    Serial.println("Stationary mode");
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void turning(int steering, int deg) {
    steering = PS4.RStickX();
    Serial.println("Steering: "+steering);
    deg = map(steering, -255, 255, 0, 180);
    if (PS4.R1()) {
        deg = 90;
    }
    steerServo.write(deg);
    if (deg < 90) {
        Serial.println("Steering engaged, turning left");
    } else if (deg > 90) {
        Serial.println("Steering engaged, turning right");
    } else if (deg == 90) {
        Serial.println("Steering disengaged");
    }
}

void move(int speed, int actualSpeed) {
    if (speed > 0) {
        drive(actualSpeed);
    } else if (speed<0) {
        reverse(actualSpeed);
    } else if (speed == 0 || PS4.L1()) {
        stop();
    }
}

void loop() {
    if (PS4.isConnected()) {
    speed = PS4.LStickY();
    actualSpeed = map(speed, -255, 0, 255, 1023);
    Serial.println("Speed: "+speed);
    Serial.println("ActualSpeed: "+actualSpeed);


        PS4.setLed(0, 255, 0);
        PS4.sendToController();
        move(speed, actualSpeed);
        turning(steering, deg);
    } else {
        Serial.print("Fail");
    }
    delay(1000);
}

// screen /dev/cu.usbserial-0001 115200