#include <Arduino.h>
#include <math.h>
#include <MQ135.h>
#include <DHT.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#define pin A5
#define DHTPIN 2
#define out 7
#define DHTTYPE DHT11
MQ135 mq135_sensor(pin);
DHT dht(DHTPIN, DHTTYPE);
float Ro = 4.78;

double co2, co, nh4;
float temperature, humidity;

double Resistance(int raw)
{
  double vlaue = (double)raw;
  return (10 * (1023 - vlaue) / vlaue);
}

double corrResistance(int raw)
{
  return Resistance(raw) / mq135_sensor.getCorrectionFactor(temperature, humidity);
}
double Mqread()
{
  double rs = 0.0;
  for (int i = 0; i < 5; i++)
  {
    rs += corrResistance(analogRead(pin));
    delay(50);
  }
  return (rs / (float)5);
}

double GetPercentage(double *pcurve)
{
  double rs = Mqread();
  // Serial.println(rs);

  double ratio = rs / Ro;
  // Serial.println(ratio);
  double ppm = pow(10.0, ((log(ratio) - pcurve[0]) / pcurve[1]));
  return ppm;
}

double readCO2()
{
  double CO2curve[2] = {1.58, -0.3};
  return mq135_sensor.getCorrectedPPM(temperature, humidity);
  // return GetPercentage(CO2curve);
}
double readCO()
{
  double COcurve[2] = {1.6, -0.25};
  return GetPercentage(COcurve);
}
double readNH4()
{
  double NH4curve[2] = {1.9, -0.4};
  return GetPercentage(NH4curve);
}
double aqiCO()
{
  double aqi[6][4] = {{0, 1.0, 0, 50.0},
                      {1.1, 2.0, 51.0, 100.0},
                      {2.1, 10.0, 101.0, 200.0},
                      {10.1, 17.0, 201.0, 300},
                      {17.1, 34.0, 301.0, 400.0},
                      {34, 1e9, 401.0, 500}};
  int ind;
  double BPh, BPl, Ih, Il;
  double Cp = co;
  for (int i = 0; i < 6; i++)
  {
    if (Cp >= aqi[i][0] && Cp <= aqi[i][1])
    {
      BPh = aqi[i][1];
      BPl = aqi[i][0];
      Ih = aqi[i][3];
      Il = aqi[i][2];
      break;
    }
  }
  double ppm = ((Ih - Il) / (BPh - BPl)) * (Cp - BPl) + (Il);
  return ppm;
}
double aqiNH4()
{
  double aqi[6][4] = {{0, 200.0, 0, 50.0},
                      {201.0, 400.0, 51.0, 100.0},
                      {401.0, 800.0, 101.0, 200.0},
                      {801.0, 1200.0, 201.0, 300},
                      {1201.1, 1800.0, 301.0, 400.0},
                      {1800, 1e9, 401.0, 500}};
  int ind;
  double BPh, BPl, Ih, Il;
  double Cp = nh4;
  for (int i = 0; i < 6; i++)
  {
    if (Cp >= aqi[i][0] && Cp <= aqi[i][1])
    {
      BPh = aqi[i][1];
      BPl = aqi[i][0];
      Ih = aqi[i][3];
      Il = aqi[i][2];
      break;
    }
  }
  double ppm = ((Ih - Il) / (BPh - BPl)) * (Cp - BPl) + (Il);
  return ppm;
}
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(out, OUTPUT);
  // Ro = 4.78;
  dht.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  co2 = readCO2();
  co = readCO();
  nh4 = readNH4();
  double Coaqi = aqiCO();
  double NH4aqi = aqiNH4();
  double AQI = max(Coaqi, NH4aqi);
  if (AQI > 200)
  {
    digitalWrite(out, HIGH);
  }
  else
  {
    digitalWrite(out, LOW);
  }
  Serial.print(co2);
  Serial.print(",");
  Serial.print(co);
  Serial.print(",");
  // Serial.print(Coaqi);
  // Serial.print(",");
  Serial.print(nh4);
  Serial.print(",");
  // Serial.print(NH4aqi);
  // Serial.print(",");
  Serial.print(AQI);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.print(temperature);
  Serial.println(" ");
  delay(1500);
}
