#include "SensorDHT11.h"

SensorDHT11::SensorDHT11(int pin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC)
    : sensorPin(pin), dht(pin, DHT11), mqttHandler(mqttHandler), UPDATE_TOPIC(UPDATE_TOPIC) {}

void SensorDHT11::Begin() {
    dht.begin();
    Serial.println("--- Sensor DHT11 inicialized.");
}

void SensorDHT11::UpdateTemperature() {
    float temperature = dht.readTemperature();
    
    if (isnan(temperature)) {
        Serial.println("Error to read temperature of sensor DHT11.");
        return;
    }

    Serial.print("*** Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    outputDoc["state"]["reported"]["Temperature"] = temperature; 
    serializeJson(outputDoc, outputBuffer);

    mqttHandler->Publish(UPDATE_TOPIC, outputBuffer);
    
    Serial.println("* State temperature reported to MQTT");
}