/* inclusao das bibliotecas */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <TimeAlarms.h>

/* ssid e password do AP ao qual se deseja conectar */
const char* ssid = "ssid";
const char* password = "password";
/* endereco do servidor onde está instalado o ThingsBoard
// const char* mqtt_server = "192.168.X.XXX";
/* ou para o ThingsBoard live demo */
const char* mqtt_server = "demo.thingsboard.io";
/* credenciais para o device que se deseja conectar */
const char* device_token = "device_token";

/* instancia o cliente Wi-Fi */
WiFiClient wifi_client;
/* instancia o cliente MQTT */
PubSubClient mqtt_client(wifi_client);

void conectar_wifi() {
  delay(10);
  Serial.println();
  Serial.print("conectando a ");
  Serial.println(ssid);
  /* tenta iniciar a conexao com a rede Wi-Fi */
  WiFi.begin(ssid, password);
  /* verifica o status e aguarda a conexao */
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  /* imprime na serial IP da conexao Wi-Fi */
  Serial.println("");
  Serial.println("conectado ao AP");
  Serial.println("endereco IP: ");
  Serial.println(WiFi.localIP());
}

void reconectar() {
  /* loop ate que esteja reconectado com o broker MQTT */
  while (!mqtt_client.connected()) {
    /* verifica a conexao Wi-Fi */
    if (WiFi.status() != WL_CONNECTED) {
      /* reconecta com o Wi-Fi */
      conectar_wifi();
    }
    Serial.print("tentando conexao com o ThingsBoard via MQTT...");
    /* tentativa de conexao */
    if (mqtt_client.connect("wemos", device_token, NULL)) {
      Serial.println("conectado");
    } 
    else {
      Serial.print("falhou, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" tentando novamente em 5s");
      /* tenta novamente daqui a 5s */
      delay(5000);
    }
  }
}

void coletar_e_enviar_dados() {
  Serial.print("coletando dados de temperatura e umidade... ");
  /* realiza a leitura da umidade (simulado) */
  float h = random(70,95);
  /* realiza a leitura da temperatura (simulado) */
  float t = random(21,32);
  /* imprime na serial os valores lidos dos sensores */
  Serial.print("umidade: ");
  Serial.print(h);
  Serial.print(" % | temperatura: ");
  Serial.print(t);
  Serial.println(" *C ");
  /* converte os dados lidos para String */
  String temperatura = String(t);
  String umidade = String(h);
  /* cria o payload da mensagem MQTT no formato JSON */
  String payload = "{";
  payload += "\"temperatura\":"; payload += temperatura; payload += ",";
  payload += "\"umidade\":"; payload += umidade;
  payload += "}";
  /* converte os dados em formato JSON de String para char[] */
  char dados_json[100];
  payload.toCharArray(dados_json, 100);
  /* envia o pacote MQTT com os dados dos sensores */
  mqtt_client.publish( "v1/devices/me/telemetry", dados_json);
}

void setup() {
  /* configura a interface serial */
  Serial.begin(115200);
  /* conectar a rede Wi-Fi */
  conectar_wifi();
  /* conectar ao broker MQTT */
  mqtt_client.setServer(mqtt_server, 1883);
  /* programa um evento de tempo a cada 10s para enviar os dados dos sensores */
  Alarm.timerRepeat(10, coletar_e_enviar_dados);
}

void loop() {
  /* verifica status da conexao */
  if (!mqtt_client.connected()) {
    reconectar();
  }
  /* executa a funcao de loop da biblioteca TimeAlarm */
  Alarm.delay(100);
  /* executa a funcao de loop do cliente MQTT */
  mqtt_client.loop();
}
