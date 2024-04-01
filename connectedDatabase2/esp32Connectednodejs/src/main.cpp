#include <Arduino.h>

// put function declarations here:
#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "your_network_ssid";
const char *password = "your_network_password";
const char *serverUrl = "http://your_nodejs_server_ip_or_hostname:3000/data";

void setup()
{
  Serial.begin(115200);
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
  HTTPClient http;
  http.begin(serverUrl);

  // Add custom headers
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer your_access_token");

  // Make sure to replace "your_access_token" with your actual authorization token

  // Formulate the JSON payload
  String payload = "{\"dateTime\": \"" + dateTime + "\"}";

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  delay(60000); // Send data every minute
}