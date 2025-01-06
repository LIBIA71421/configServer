#ifndef SENSORDHT11_H
#define SENSORDHT11_H

#include <Arduino.h>
#include <MQTTHandler.h> 
#include <ArduinoJson.h> 
#include <DHT.h>

class SensorDHT11 {
public:
    SensorDHT11(int pin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC);
    
    void Begin();
    
    void UpdateTemperature();

private:
    int sensorPin; 
    MQTTHandler* mqttHandler; 
    const char* UPDATE_TOPIC; 

    DHT dht;
    
    StaticJsonDocument<128> outputDoc;
    char outputBuffer[128];
};

#endif // SENSORDHT11_H

