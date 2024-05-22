#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

// Pin definitions
#define Rxp2 D5 // Change these pin definitions according to your wiring
#define Txp2 D6

const char *ssid = "Debashis";
const char *password = "debashis02";
const char *serverUrl = "https://deba0208-server.onrender.com/data";
float co2, co, tvoc, nh4, pm25, AQI, Temp, Humidity;
char delimiter = ',';

SoftwareSerial Serial2(Rxp2, Txp2); // Define SoftwareSerial object

void getvalue(String Str)
{
  int delimiterIndex = Str.indexOf(delimiter);
  float array[10];
  int i = 0;
  // Splits Str into all possible tokens
  while (delimiterIndex >= 0)
  {
    array[i++] = Str.substring(0, delimiterIndex).toFloat();
    // Serial.println(token);
    Str = Str.substring(delimiterIndex + 1);
    delimiterIndex = Str.indexOf(delimiter);
  }
  co2 = array[0];
  co = array[1];
  // coAqi = array[2];
  nh4 = array[2];
  pm25 = array[3];
  tvoc = array[4];
  AQI = array[5];
  Humidity = array[6];
  Temp = array[7];
}

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(100);

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
  if (Serial2.available())
  {
    String s = Serial2.readString();
    getvalue(s);
    String dateTime = "2024-03-31T12:00:00";

    // Send the data to the Node.js server
    HTTPClient http;
    WiFiClient client;
    http.begin(client, serverUrl);
    // http.begin(serverUrl);
    // Add custom headers
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer 123456789");

    // Formulate the JSON payload
    String payload = "{\"co2\": \"" + String(co2) + "\", \"co\": \"" + String(co) + "\", \"pm2.5\": \"" + String(pm25) + "\", \"nh4\": \"" + String(nh4) + "\", \"AQI\": \"" + String(AQI) + "\", \"TVOC\": \"" + String(tvoc) + "\", \"Temperature\": \"" + String(Temp) + "\", \"Humidity\": \"" + String(Humidity) + "\"}";
    // String payload = "{\" dateTime\":\"" + dateTime + "\"}";
    int httpResponseCode = http.POST(payload);
    Serial.print(co2);
    Serial.print(",");
    Serial.print(co);
    Serial.print(",");
    Serial.print(pm25);
    Serial.print(",");
    Serial.print(nh4);
    Serial.print(",");
    Serial.print(tvoc);
    Serial.print(",");
    Serial.print(AQI);
    Serial.print(",");
    Serial.print(Humidity);
    Serial.print(",");
    Serial.print(Temp);
    Serial.println(" ");
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
  }

  delay(60000); // Send data every minute
}
