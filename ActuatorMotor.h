#ifndef ACTUATORMOTOR_H
#define ACTUATORMOTOR_H

#include "MQTTHandler.h"
#include <ArduinoJson.h>

class ActuatorMotor {
  private:
    int motorPin;
    int motorState = 0;
    MQTTHandler* mqttHandler;
    const char* UPDATE_TOPIC;

    StaticJsonDocument<128> outputDoc;
    char outputBuffer[128];

  public:
    ActuatorMotor(int pin, MQTTHandler* mqttHandler, const char* UPDATE_TOPIC);
    void Begin();
    void SetMotorState(int state);
    void ReportState();
    void HandleIncomingMessage(const String& MESSAGE);
};

#endif // ACTUATORMOTOR_H
