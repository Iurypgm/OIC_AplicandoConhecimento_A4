#include <WiFi.h>
#include <PubSubClient.h>

#define TRIG 5
#define ECHO 18

#define RED 16
#define GREEN 4
#define BLUE 2

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "lixeira_iot/ocupacao";

WiFiClient espClient;
PubSubClient client(espClient);

long duracao;
float distancia;
float porcentagem;

void conectarWiFi() {
  Serial.print("Conectando ao WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT... ");

    String clientId = "ESP32_Lixeira_";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!");
    } else {
      Serial.print("falha, codigo=");
      Serial.print(client.state());
      Serial.println(" | nova tentativa em 2 segundos");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // começa com tudo apagado
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  conectarWiFi();

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {

  if (!client.connected()) {
    conectarMQTT();
  }

  client.loop();

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duracao = pulseIn(ECHO, HIGH);
  distancia = duracao * 0.034 / 2;

  porcentagem = ((400 - distancia) / 400.0) * 100;

  if (porcentagem < 0) porcentagem = 0;
  if (porcentagem > 100) porcentagem = 100;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print(" cm | Ocupacao: ");
  Serial.print((int)porcentagem);
  Serial.print("% - ");

  String status;

  if (porcentagem >= 90) {
    status = "Lixeira quase cheia. Recomenda-se coleta imediata.";
    Serial.println(status);

    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  }
  else if (porcentagem >= 60) {
    status = "Lixeira acima de 60% da capacidade.";
    Serial.println(status);

    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
  }
  else {
    status = "Lixeira com capacidade disponivel.";
    Serial.println(status);

    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
  }

  String mensagem = "{";
  mensagem += "\"distancia\":";
  mensagem += String(distancia);
  mensagem += ",\"ocupacao\":";
  mensagem += String((int)porcentagem);
  mensagem += ",\"status\":\"";
  mensagem += status;
  mensagem += "\"}";

  client.publish(mqtt_topic, mensagem.c_str());

  Serial.print("MQTT enviado no topico ");
  Serial.print(mqtt_topic);
  Serial.print(": ");
  Serial.println(mensagem);

  delay(1000);
}
