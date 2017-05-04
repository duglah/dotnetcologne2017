#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const String serverAdress = "adress";
const char* ssid = "SSID";
const char* password = "PW";

void setup() {
  Serial.begin(115200); //Serielleausgabe starten -> Tools > Serial Monitor
}

void loop() {
  connect();
  getStatus();
  delay(1000);
}

void connect() {
  delay(10);

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Already connected...");
    return;
  }

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("WiFi connected");
}

void getStatus() {
  HTTPClient http;
  http.begin(serverAdress);
  
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.println(http.getString());
  }
  else {
    Serial.printf("Request failed: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();
}

