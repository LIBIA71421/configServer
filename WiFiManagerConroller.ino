#include <FS.h>
#include <LittleFS.h>  // Librería para usar LittleFS
#include <WiFi.h>
#include <WiFiManager.h>  // Librería para manejar Wi-Fi fácilmente
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

WiFiClientSecure espClient;
PubSubClient client(espClient);

const char* awsEndpoint = "a16qvxfcql3rxm-ats.iot.us-east-2.amazonaws.com"; // Endpoint de tu AWS IoT Core
const int awsPort = 8883; // Puerto MQTT para AWS IoT (SSL)

// Tópico MQTT
const char* mqttTopic = "$aws/things/rootrise_0001/shadow/update";

WiFiManager wifiManager;

// Declarar la función mqttCallback
void mqttCallback(char* topic, byte* payload, unsigned int length);

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando ESP32...");
  // Inicializar sistema de archivos
  if (!LittleFS.begin()) {
    Serial.println("Error al montar LittleFS");
    return;
  }

  // Leer los certificados desde el sistema de archivos
  File cert = LittleFS.open("/cert.pem.crt", "r");
  File privateKey = LittleFS.open("/privateKey.pem.key", "r");
  File ca = LittleFS.open("/ca.pem", "r");

  if (cert) {
    Serial.println("Certificado (cert.pem.crt) abierto correctamente");
  } else {
    Serial.println("Error al abrir cert.pem.crt");
  }

  if (privateKey) {
    Serial.println("Clave privada (privateKey.pem.key) abierta correctamente");
  } else {
    Serial.println("Error al abrir privateKey.pem.key");
  }

  if (ca) {
    Serial.println("Certificado raíz (ca.pem) abierto correctamente");
  } else {
    Serial.println("Error al abrir ca.pem");
  }

  if (cert && privateKey && ca) {
    espClient.setCertificate(cert.readString().c_str());
    espClient.setPrivateKey(privateKey.readString().c_str());
    espClient.setCACert(ca.readString().c_str());
    Serial.println("Certificados cargados correctamente");
    cert.close();
    privateKey.close();
    ca.close();
  } else {
    Serial.println("Error al leer uno o más certificados");
  }

  // Conectar al Wi-Fi
  wifiManager.autoConnect("RootRise_AP");

  // Configurar el cliente MQTT
  client.setServer(awsEndpoint, awsPort);
  client.setCallback(mqttCallback);

  // Intentar conexión MQTT
  while (!client.connected()) {
    if (client.connect("rootrise_0001")) {  // ID del cliente MQTT
      Serial.println("Conectado a AWS IoT");
      client.subscribe(mqttTopic);  // Suscribirse al tópico
    } else {
      Serial.print("Error de conexión: ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void loop() {
  client.loop();  // Mantén la conexión MQTT
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
