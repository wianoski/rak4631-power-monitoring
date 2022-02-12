#ifndef ENERGY_SENSOR_H
#define ENERGY_SENSOR_H

#include <Arduino.h>
#include <ATM90E32.h>
#include <vector>
#include "EnergyConstants.h"
#include "EnergyReadings.h"

#include "settings/AppSettings.h"

class EnergySensor
{
public:
    EnergySensor(ApplicationSettings* settings);
    virtual ~EnergySensor();

    bool begin(size_t numSensors, uint8_t *chipSelects);
    void read();
    void printReadings();
    EnergyReadings* getReadings();

protected:
    std::vector<ATM90E32*> _sensors;
    std::vector<EnergyReadings> _readings;
    ApplicationSettings *_settings;
};

#endif
