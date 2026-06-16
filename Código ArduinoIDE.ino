#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <DHT.h>
#include <MAX30100_PulseOximeter.h>

// ===== WIFI =====
const char* ssid = "";
const char* password = "";

// ===== MQTT =====
const char* mqtt_server = "9ca03c36523a4fbaa8ffdfb128beef7b.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "CarePlus";
const char* mqtt_password = "CarePlus321@";

const char* topic_bpm  = "careplus/bpm";
const char* topic_temp = "careplus/temp";

// ===== DHT11 =====
#define DHT_PIN 4
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// ===== MAX30100 =====
PulseOximeter pox;
#define REPORTING_PERIOD_MS 1000

WiFiClientSecure espClient;
PubSubClient client(espClient);

float bpm = 0;
float spo2 = 0;
float temperatura = 0;
float umidade = 0;

bool sensorOk = false;

unsigned long lastReport = 0;
unsigned long lastPublish = 0;
unsigned long lastDHT = 0;

void onBeatDetected() {
  Serial.println("Batimento detectado!");
}

void setupWifi() {
  Serial.print("Conectando WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");

    if (client.connect("ESP32_CarePlus", mqtt_user, mqtt_password)) {
      Serial.println("OK");
    } else {
      Serial.println("Falhou");
      delay(3000);
    }
  }
}

void lerDHT() {
  if (millis() - lastDHT >= 2000) {
    lastDHT = millis();

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t)) temperatura = t;
    if (!isnan(h)) umidade = h;
  }
}

void setup() {
  Serial.begin(115200);

  Serial.println("CARE PLUS");

  dht.begin();

  Wire.begin(21, 22);

  Serial.println("Inicializando MAX30100...");

  if (!pox.begin()) {
    Serial.println("MAX30100 NAO ENCONTRADO");
    sensorOk = false;
  } else {
    Serial.println("MAX30100 OK");
    pox.setIRLedCurrent(MAX30100_LED_CURR_50MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
    sensorOk = true;
  }

  setupWifi();

  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {

  lerDHT();

  if (sensorOk) {
    pox.update();
  }

  if (!client.connected()) {
    reconnectMQTT();
  }

  client.loop();

  if (millis() - lastReport >= REPORTING_PERIOD_MS) {

    lastReport = millis();

    if (sensorOk) {
      bpm = pox.getHeartRate();
      spo2 = pox.getSpO2();
    }

    Serial.print("BPM: ");
    Serial.print(bpm);

    Serial.print(" | SpO2: ");
    Serial.print(spo2);

    Serial.print("% | Temp: ");
    Serial.print(temperatura);

    Serial.print("C | Umidade: ");
    Serial.print(umidade);

    Serial.println("%");
  }

  if (millis() - lastPublish >= 10000) {

    lastPublish = millis();

    String payloadBpm =
      "{\"batimentos\":" + String(bpm) +
      ",\"spo2\":" + String(spo2) + "}";

    String payloadTemp =
      "{\"temperatura\":" + String(temperatura) +
      ",\"umidade\":" + String(umidade) + "}";

    client.publish(topic_bpm, payloadBpm.c_str());
    client.publish(topic_temp, payloadTemp.c_str());

    Serial.println("Dados enviados MQTT");
  }
}
