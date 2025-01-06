#ifndef ACTUATORFAN_H
#define ACTUATORFAN_H

#include "MQTTHandler.h"
#include <ArduinoJson.h>

class ActuatorFan {
  private:
    int fanPin;
    int fanState = 0;
    MQTTHandler* mqttHandler;
    const char* UPDATE_TOPIC;

    StaticJsonDocument<128> outputDoc;
    char outputBuffer[128];

  public:
    ActuatorFan(int pin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC);
    void Begin();
    void SetFanState(int state);
    void ReportState();
    void HandleIncomingMessage(const String& MESSAGE);
};

#endif // ACTUATORFAN_H
