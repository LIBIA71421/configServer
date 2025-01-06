#include "SensorFC28.h"

SensorFC28::SensorFC28(int pin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC)
    : sensorPin(pin), mqttHandler(mqttHandler), UPDATE_TOPIC(UPDATE_TOPIC) {}

void SensorFC28::Begin() {
    pinMode(sensorPin, INPUT); 
    Serial.println("--- Sensor FC-28 soil moisture initialized");
}

int SensorFC28::GetRawHumidity() {
    int humidity = analogRead(sensorPin); 

    if (humidity == 4095) {
        Serial.println("Error: out-of-range reading (4095).");
        delay(1000);  
        return -1;    
    }

    return humidity; 
}

int SensorFC28::CalculateHumidityPercentage(int rawHumidity) {
    return map(rawHumidity, lecturaH, lecturaS, 100, 0);
}

void SensorFC28::UpdateHumidity() {
    int rawHumidity = GetRawHumidity();
    if (rawHumidity == -1) {
        return; 
    }

    int humedadPercent = CalculateHumidityPercentage(rawHumidity);

    Serial.print("*** Humidity: ");
    Serial.print(humedadPercent);
    Serial.println("%");

    outputDoc["state"]["reported"]["humidity"] = humedadPercent;
    serializeJson(outputDoc, outputBuffer);
    mqttHandler->Publish(UPDATE_TOPIC, outputBuffer);
    
    Serial.println("* State humidity reported to MQTT");
}