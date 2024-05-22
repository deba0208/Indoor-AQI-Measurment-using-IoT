#include <Arduino.h>

// put function declarations here:
// #include <WiFi.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Redmi Note 9 Pro Max";
const char *password = "rimpa741302";
const char *serverUrl = "http://192.168.7.238:3000/data";

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop()
{
  // Get the current date/time (example)
  String dateTime = "2024-03-31T12:00:00";

  // Send the data to the Node.js server
  WiFiClient client;
  HTTPClient http;
//  HTTPClient http;
  http.begin(client, serverUrl);
  http.addHeader("Content-Type", "application/json");

  String data = "{\"key\": \"value\"}"; // Replace with your data
  int httpResponseCode = http.POST(data);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  delay(6000); // Send data every minute
}