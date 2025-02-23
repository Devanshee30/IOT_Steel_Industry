    #include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverUrl = "http://192.168.1.100:5000/receive_data"; // RPi Flask Server IP

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("WiFi Connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"usage_kWh\":3.17,\"lagging_kVarh\":2.95,\"leading_kVarh\":0,\"lagging_pf\":73.21,\"leading_pf\":100}";

    int httpResponseCode = http.POST(payload);
    Serial.print("Response: ");
    Serial.println(httpResponseCode);
    
    http.end();
    delay(900000);  // Send data every 15 minutes
  } else {
    Serial.println("WiFi Disconnected");
  }
}
