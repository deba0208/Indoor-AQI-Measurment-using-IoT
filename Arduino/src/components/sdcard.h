#include <Arduino.h>
#include <SD.h>
File file;
int CS_PIN;
void initializeSD(int pin)
{
    CS_PIN = pin;
    pinMode(CS_PIN, OUTPUT);

    if (SD.begin())
    {
    }
    else
    {
        return;
    }
}
int openFileToWrite(char filename[])
{
    file = SD.open(filename, FILE_WRITE);

    if (file)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int writeToFile(String text)
{
    if (file)
    {
        file.println(text);
        return 1;
    }
    else
    {
        return 0;
    }
}
void closeFile()
{
    if (file)
    {
        file.close();
    }
}
void writeEntryToFile(String entry)
{
    openFileToWrite("room3.txt");
    Serial.println(entry);
    writeToFile(entry);
    closeFile();
}