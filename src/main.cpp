#include <Arduino.h>
#include <PS4Controller.h>

int ENA;
int IN1;
int IN2;
int ENB;
int IN3;
int IN4;

void setup() {
    Serial.begin(115200);
    PS4.begin();
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

