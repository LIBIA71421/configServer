#ifndef SENSORFC28_H
#define SENSORFC28_H

#include <Arduino.h>
#include <MQTTHandler.h> 
#include <ArduinoJson.h> 

class SensorFC28 {
public:
    SensorFC28(int pin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC);
    
    void Begin();
    
    void UpdateHumidity();

private:
    int sensorPin; 
    MQTTHandler* mqttHandler; 
    const char* UPDATE_TOPIC; 

    const int lecturaS = 4095;     
    const int lecturaH = 1020; 

    int GetRawHumidity(); 
    int CalculateHumidityPercentage(int rawHumidity); 

    StaticJsonDocument<128> outputDoc;
    char outputBuffer[128];
};

#endif // SENSORFC28_H