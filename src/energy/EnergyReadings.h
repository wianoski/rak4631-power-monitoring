#ifndef DYCODEX_ENERGY_READINGS_H
#define DYCODEX_ENERGY_READINGS_H
#include <stdint.h>
#include "EnergyConstants.h"

typedef struct
{
    float voltage;
    float temperature;
    float frequency;
    float lineVoltage[ENERGYIC_NUM_INPUTS];
    float current[ENERGYIC_NUM_INPUTS];
    float realPower[ENERGYIC_NUM_INPUTS];
    float vaPower[ENERGYIC_NUM_INPUTS];
    float powerFactor[ENERGYIC_NUM_INPUTS];
    uint16_t sys0;
    uint16_t sys1;
    uint16_t en0;
    uint16_t en1;
} EnergyReadings;

#endif