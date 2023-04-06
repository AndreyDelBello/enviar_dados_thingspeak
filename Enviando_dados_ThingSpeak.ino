#include <ThingSpeak.h>
#include "DHT.h"
#include <ESP8266WiFi.h>
 
#define DHTPIN 4 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
 
DHT dht(DHTPIN, DHTTYPE);

#define SSID "****"
#define SENHA "****"
#define IDCANAL numeros

WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.print("Conectando a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, SENHA);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\nConectado a rede com sucesso!");
  ThingSpeak.begin(client);

  dht.begin();
}

void loop() {
  delay(15000);

  float humidade = dht.readHumidity();
 
  float temperatura = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidade) || isnan(temperatura)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  ThingSpeak.setField(1, temperatura);
  ThingSpeak.setField(2, humidade);

  int retorno = ThingSpeak.writeFields(IDCANAL, "SuaChaveAqui");

  if(retorno == 200) {
    Serial.println("Dados gravados corretamente no ThingSpeak");
  } else {
    Serial.println("Falha na gravação!");
  }
  delay(15000);
  
  Serial.print(F("Humidade: "));
  Serial.print(humidade);
  Serial.print(F("%  Temperatura: "));
  Serial.print(temperatura);
  Serial.print(F("°C "));

}
