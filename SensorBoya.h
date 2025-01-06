#ifndef SENSOR_BOYA_H
#define SENSOR_BOYA_H

#include <ArduinoJson.h>
#include "MQTTHandler.h"

class SensorBoya {
public:
    SensorBoya(int pin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC);
    void Begin();
    void UpdateBoya();
    int levelWater();

private:
    int sensorPin;
    MQTTHandler* mqttHandler;
    const char* UPDATE_TOPIC;

    StaticJsonDocument<128> outputDoc;
    char outputBuffer[128];
};

#endif