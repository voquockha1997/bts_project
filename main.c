#include <stdio.h> 
#include <time.h>
#include <signal.h>

#include "main.h"
#include "sensor.h"
#define TEMP_SET 35

volatile sig_atomic_t sigintFlag = 0;

void onSigInt(int signum){
    sigintFlag = 1;
}


int main(int argc, char **argv)
{ 
    signal(SIGINT, onSigInt);

    char **sensorNames;
    int sensorNamesCount;
    if(argc > 1)
    {
        sensorNames = argv + 1;
        sensorNamesCount = argc - 1;
    }    
    else
    {
        sensorNames = NULL;
        sensorNamesCount = 0;
    }    

    SensorList *sensorList = GetSensors(sensorNames, sensorNamesCount);
    if(sensorList->SensorCount == 0)
    {
        printf("No sensors found - exiting.\n");
        return 0;
    }
    printf("Attached Sensors: %d\n", sensorList->SensorCount);

    while(!sigintFlag)
    {
        for(int i = 0; i < sensorList->SensorCount; i++)
        {
            float temperature = ReadTemperature(sensorList->Sensors[i]);
            LogTemperature(sensorList->Sensors[i], temperature);
            if (temperature > TEMP_SET)
            {
                /* Set ON GPIO */
                printf("Warning temp high\n");
            }
        }       
    }       
    Cleanup(sensorList);   
}


void Cleanup(SensorList *sensorList)
{
    printf("Exiting...\n");
    FreeSensors(sensorList);
}

void ReadTemperatureLoop(SensorList *sensorList)
{
    while(!sigintFlag)
    {
        for(int i = 0; i < sensorList->SensorCount; i++)
        {
            float temperature = ReadTemperature(sensorList->Sensors[i]);
            LogTemperature(sensorList->Sensors[i], temperature);
        }       
    }
}

void LogTemperature(Sensor *sensor, float temperature)
{
    time_t currentTime;
    time(&currentTime);

    char dateTimeStringBuffer[32];
    strftime(dateTimeStringBuffer, 32, "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

    printf("%s - %s - %.2fC\n", dateTimeStringBuffer, sensor->SensorName, temperature);
}
