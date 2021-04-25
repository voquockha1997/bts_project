#ifndef _main_h
#define _main_h 

#include "sensor.h"

void Cleanup(SensorList *sensorList);
void ReadTemperatureLoop(SensorList *sensorList);
void LogTemperature(Sensor *sensor, float temperature);

#endif /* _main_h */