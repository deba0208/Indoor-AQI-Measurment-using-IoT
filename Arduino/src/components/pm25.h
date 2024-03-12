#include <Arduino.h>
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