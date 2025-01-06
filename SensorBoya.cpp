#include "SensorBoya.h"

SensorBoya::SensorBoya(int pin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC)
    : sensorPin(pin), mqttHandler(mqttHandler), UPDATE_TOPIC(UPDATE_TOPIC) {}

void SensorBoya::Begin() {
    pinMode(sensorPin, INPUT_PULLUP); 
    Serial.println("--- Sensor de boya inicialized");
}

int SensorBoya::levelWater() {
    int estado = digitalRead(sensorPin);
    int nivelAguaSuficiente = (estado == LOW) ? 0 : 1; 
    return nivelAguaSuficiente;
}

void SensorBoya::UpdateBoya() {
    int nivelAguaSuficiente = verificarNivelAgua();

    if (nivelAguaSuficiente == 1) {
        Serial.println("*** Sufficient water level");
        outputDoc["state"]["reported"]["WaterLevel"] = 1; 
    } else {
        Serial.println("*** Insufficient water level");
        outputDoc["state"]["reported"]["WaterLevel"] = 0; 
    }

    serializeJson(outputDoc, outputBuffer);
    mqttHandler->Publish(UPDATE_TOPIC, outputBuffer);
    Serial.println("* State boya reported to MQTT");
}