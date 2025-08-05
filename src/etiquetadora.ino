#include <Arduino.h>

int valorPin = 0;
void setup() {
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);
    pinMode(8, INPUT);
}

void loop() {
    valorPin = digitalRead(8);
    Serial.print("Valor pin8: ");
    Serial.println(valorPin);
    // Your main code here
}
