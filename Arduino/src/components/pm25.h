#include <Arduino.h>
#include <./components/AquiCalculation.h>
int measuringpin = A0;
int samplingTime = 280;

float voMeasure = 0;
float calcVoltage = 0;
float dustDensity = 0;

float readPm25()
{
    delayMicroseconds(samplingTime);
    voMeasure = analogRead(measuringpin);
    calcVoltage = voMeasure * (5.0 / 1024.0);
    dustDensity = 170 * calcVoltage - 0.1;
    return dustDensity;
}

double aqiPM25(double pm25)
{
    double aqi[6][4] = {{0, 30.0, 0, 50.0},
                        {31.0, 60.0, 51.0, 100.0},
                        {61.0, 90.0, 101.0, 200.0},
                        {91.0, 120.0, 201.0, 300},
                        {121.1, 250.0, 301.0, 400.0},
                        {251, 1e9, 401.0, 500}};

    return aqiCalculation(aqi, pm25);
}