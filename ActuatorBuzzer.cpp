#include "ActuatorBuzzer.h"
#include <Arduino.h>

ActuatorBuzzer::ActuatorBuzzer(int buzzerPin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC)
    : buzzerPin(buzzerPin), mqttHandler(mqttHandler), UPDATE_TOPIC(UPDATE_TOPIC) {}


void ActuatorBuzzer::Begin() {
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW); 
    Serial.println("+ Buzzer initialized and set to OFF");
    ReportState();
}

void ActuatorBuzzer::SetBuzzerState(int state) {
    if (buzzerState != state) {
        buzzerState = state;
        digitalWrite(buzzerPin, buzzerState ? HIGH : LOW);
        if (buzzerState) {
            Serial.println("+ Buzzer is ON");
        } else {
            Serial.println("+ Buzzer is OFF");
        }
        ReportState();
    }
}

void ActuatorBuzzer::ReportState() {
    outputDoc["state"]["reported"]["Buzzer"] = buzzerState;
    serializeJson(outputDoc, outputBuffer);
    mqttHandler->Publish(UPDATE_TOPIC, outputBuffer);
    Serial.println("+ Buzzer state reported to MQTT");
}

void ActuatorBuzzer::HandleIncomingMessage(const String& MESSAGE) {
    StaticJsonDocument<128> inputDoc;
    DeserializationError error = deserializeJson(inputDoc, MESSAGE);
    if (!error) {
        int newState = inputDoc["state"]["Buzzer"].as<int>();
        SetBuzzerState(newState);
    } else {
        Serial.println("Failed to parse JSON message for buzzer state");
    }
}