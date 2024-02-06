#include <Arduino.h>
#include <WiFi.h>
#include <ThingSpeak.h>
// put function declarations here:

#define CHANNEL_ID 2349866
#define CHANNEL_API_KEY "9TCHOR19YOX9WNMD"

#define LED_BUILTIN 15
#define Rxp2 16
#define Txp2 17

#define WIFI_NETWORK "Debashis"
#define WIFI_PASSWORD "debashis02"
#define WIFI_TIMEOUT_MS 20000

// ardunio values
float co2, co, coAqi, nh4, nh4aqi, AQI, Temp, Humidity;
char delimiter = ',';
WiFiClient Client;
void connectToWiFi()
{
  Serial.print("Connecting to wifi: ");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttempttime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttempttime < WIFI_TIMEOUT_MS)
  {
    // Serial.print(".");
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    // Serial.println("Failed!");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1500);
    digitalWrite(LED_BUILTIN, LOW);
  }
  // else
  // {
  //   Serial.print("connected!");
  //   Serial.println(WiFi.localIP());
  // }
}

void getvalue(String Str)
{
  int delimiterIndex = Str.indexOf(delimiter);
  float array[6];
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
  // nh4aqi = array[4];
  AQI = array[3];
  Temp = array[4];
  Humidity = array[5];
}
void setup()
{
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, Rxp2, Txp2);
  connectToWiFi();
  ThingSpeak.begin(Client);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  String s = Serial2.readString();
  // if (s != NULL)
  // {
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   // delay(500);
  // }
  // digitalWrite(LED_BUILTIN, LOW);
  getvalue(s);
  // delay(2000);
  ThingSpeak.setField(1, co2);
  ThingSpeak.setField(2, co);
  // ThingSpeak.setField(3, coAqi);
  ThingSpeak.setField(3, nh4);
  // ThingSpeak.setField(5, nh4aqi);
  ThingSpeak.setField(6, AQI);
  ThingSpeak.setField(7, Temp);
  ThingSpeak.setField(8, Humidity);
  ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);
  Serial.println(s);

  delay(15005);
}
// put function definitions here:
