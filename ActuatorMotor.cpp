#include "ActuatorMotor.h"
#include <Arduino.h>

ActuatorMotor::ActuatorMotor(int pin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC)
    : motorPin(pin), mqttHandler(mqttHandler), UPDATE_TOPIC(UPDATE_TOPIC) {}

void ActuatorMotor::Begin() {
    pinMode(motorPin, OUTPUT);
    digitalWrite(motorPin, HIGH); 
    Serial.println("+ Motor initialized and set to OFF");
    ReportState();
}

void ActuatorMotor::SetMotorState(int state) {
    if (motorState != state) {
        motorState = state;
        digitalWrite(motorPin, motorState ? HIGH : LOW);
        if (motorState) {
            Serial.println("+ Motor is OFF");
        } else {
            Serial.println("+ Motor is ON");
        }
        ReportState();
    }
}

void ActuatorMotor::ReportState() {
    outputDoc["state"]["reported"]["WaterBomb"] = motorState;
    serializeJson(outputDoc, outputBuffer);
    mqttHandler->Publish(UPDATE_TOPIC, outputBuffer);
    Serial.println("+ Motor state reported to MQTT");
}

void ActuatorMotor::HandleIncomingMessage(const String& MESSAGE) {
    StaticJsonDocument<128> inputDoc;
    DeserializationError error = deserializeJson(inputDoc, MESSAGE);
    if (!error) {
        int newState = inputDoc["state"]["WaterBomb"].as<int>();
        SetMotorState(newState);
    } else {
        Serial.println("Failed to parse JSON message for motor state");
    }
}
