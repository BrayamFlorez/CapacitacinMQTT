#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define Photoresistor A0 
char valor [13];
String stvalor;

const char* ssid = "realme";
const char* password = "12011201";
const char* mqtt_server = "broker.emqx.io";
const char* topicoS = "ufpstest";


WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connectando a: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connectado");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  
  while (!client.connected()) {
    Serial.println("ups, nos desconectamos");    
    String clientId = "ufps";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado");
      client.publish(topicoS, valor);
      
    } else {
      
      Serial.print("error, rc=");
      Serial.print(client.state());
      Serial.println(" intentemos de nuevo en 3 segundos");
      delay(3000);
      
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  
}

void loop() {
  
  stvalor = "lectura: ";
  stvalor+=analogRead(Photoresistor);
  stvalor.toCharArray(valor,13);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  Serial.print("mensaje publicado: ");
  Serial.println(valor);
  client.publish(topicoS, valor);
  delay(1000);
}
