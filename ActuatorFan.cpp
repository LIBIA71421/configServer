#include "ActuatorFan.h"
#include <Arduino.h>

ActuatorFan::ActuatorFan(int pin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC)
    : fanPin(pin), mqttHandler(mqttHandler), UPDATE_TOPIC(UPDATE_TOPIC) {}

void ActuatorFan::Begin() {
    pinMode(fanPin, OUTPUT);
    digitalWrite(fanPin, HIGH); 
    Serial.println("+ Fan initialized and set to OFF");
    ReportState();
}

void ActuatorFan::SetFanState(int state) {
    if (fanState != state) {
        fanState = state;
        digitalWrite(fanPin, fanState ? HIGH : LOW);
        if (fanState) {
            Serial.println("+ Fan is OFF");
        } else {
            Serial.println("+ Fan is ON");
        }
        ReportState();
    }
}

void ActuatorFan::ReportState() {
    outputDoc["state"]["reported"]["Fan"] = fanState;
    serializeJson(outputDoc, outputBuffer);
    mqttHandler->Publish(UPDATE_TOPIC, outputBuffer);
    Serial.println("+ Fan state reported to MQTT");
}

void ActuatorFan::HandleIncomingMessage(const String& MESSAGE) {
    StaticJsonDocument<128> inputDoc;
    DeserializationError error = deserializeJson
    
    (inputDoc, MESSAGE);
    if (!error) {
        int newState = inputDoc["state"]["Fan"].as<int>();
        SetFanState(newState);
    } else {
        Serial.println("Failed to parse JSON message for fan state");
    }
}
