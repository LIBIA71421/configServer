#include <Arduino.h>
#include "WiFiConnection.h"
#include "MQTTHandler.h"
#include "ActuatorMotor.h"
#include "SensorFC28.h"
#include "ActuatorBuzzer.h"
#include "SensorBoya.h"
#include "ActuatorFan.h"
#include "SensorDHT11.h"

const char* WIFI_SSID = "0";
const char* WIFI_PASS = "0";
const char* MQTT_BROKER = "a16qvxfcql3rxm-ats.iot.us-east-2.amazonaws.com";
const int MQTT_PORT = 8883;
const char* CLIENT_ID = "rootrise_0001";
const char* UPDATE_TOPIC = "$aws/things/rootrise_0001/shadow/update";
const char* UPDATE_ACCEPTED_TOPIC = "$aws/things/rootrise_0001/shadow/update/delta";

const char AMAZON_ROOT_CA1[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m
-----END CERTIFICATE-----
)EOF";

const char CERTIFICATE[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAK3e6eImwUCKO78Nao2twCjriutng==
-----END CERTIFICATE-----
)KEY";

const char PRIVATE_KEY[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAzkxu00mimG5H3dpIqzlHv+Yg/QisYE58s=
-----END RSA PRIVATE KEY-----
)KEY";


const int MOTOR_PIN = 23;
const int MOISTURE_SENSOR_PIN = 34;
const int BUZZER_PIN = 22;  
const int BOYA_PIN = 4; 
const int FAN_PIN = 19;  
const int DHT_PIN = 21;

MQTTHandler mqttHandler(MQTT_BROKER, MQTT_PORT, CLIENT_ID, UPDATE_TOPIC, UPDATE_ACCEPTED_TOPIC);
WiFiConnection wifi(WIFI_SSID, WIFI_PASS);

ActuatorMotor actuatorMotor(MOTOR_PIN, &mqttHandler, UPDATE_TOPIC);
SensorFC28 sensorFC28(MOISTURE_SENSOR_PIN, &mqttHandler,UPDATE_TOPIC);
ActuatorBuzzer buzzer(BUZZER_PIN, &mqttHandler, UPDATE_TOPIC);   
SensorBoya sensorBoya(BOYA_PIN, &mqttHandler, UPDATE_TOPIC);
ActuatorFan actuatorFan(FAN_PIN, &mqttHandler, UPDATE_TOPIC);   
SensorDHT11 sensorDHT11(DHT_PIN, &mqttHandler, UPDATE_TOPIC);

void callback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println("Message received on topic " + String(topic) + ": " + message);

    if (String(topic) == UPDATE_ACCEPTED_TOPIC) {
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, message);
         
         if (doc.containsKey("state")) {
            JsonObject state = doc["state"];

            if (state.containsKey("WaterBomb")) {
                buzzer.SetBuzzerState(0);
                actuatorFan.SetFanState(0);
                actuatorMotor.HandleIncomingMessage(message);
            }

            if (state.containsKey("Buzzer")) {
                actuatorMotor.SetMotorState(0); 
                actuatorFan.SetFanState(0); 
                buzzer.HandleIncomingMessage(message);
            }

            if (state.containsKey("Fan")) {
                actuatorMotor.SetMotorState(0); 
                buzzer.SetBuzzerState(0); 
                actuatorFan.HandleIncomingMessage(message);
            }

        } else {
            Serial.println("No valid 'state' key found in the message");
        }

    }
}
void Connect() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    
    wifi.Connect();
    mqttHandler.SetCertificates(AMAZON_ROOT_CA1, CERTIFICATE, PRIVATE_KEY);
    mqttHandler.SetCallback(callback);
    mqttHandler.Connect();

    actuatorMotor.Begin();
    sensorFC28.Begin();
    buzzer.Begin();
    sensorBoya.Begin();
    actuatorFan.Begin();
    sensorDHT11.Begin();
}

void loop() {
    if (!mqttHandler.IsConnected()) {
        mqttHandler.Connect();
    }
    mqttHandler.Loop();
    sensorFC28.UpdateHumidity();
    sensorBoya.UpdateBoya();
    sensorDHT11.UpdateTemperature();

    delay(15000); 
}

