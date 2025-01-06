#ifndef ACTUATOR_BUZZER_H
#define ACTUATOR_BUZZER_H

#include <ArduinoJson.h>
#include "MQTTHandler.h"

class ActuatorBuzzer {
private:
    int buzzerPin;
    int buzzerState = 0; 
    MQTTHandler* mqttHandler;
    const char* UPDATE_TOPIC;
    char outputBuffer[256];
    StaticJsonDocument<256> outputDoc;

public:
    ActuatorBuzzer(int buzzerPin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC);
    void ReportState();
    void Begin();
    void SetBuzzerState(int state);
    void HandleIncomingMessage(const String& MESSAGE);
};

#endif