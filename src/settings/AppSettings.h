#ifndef DYCODEX_POWTRAX_APP_SETTINGS
#define DYCODEX_POWTRAX_APP_SETTINGS

#include <stdint.h>

typedef struct
{
    uint16_t gain;
    char name[30];
    uint16_t cal;
    float currentMultiplier;
    float powerMultiplier;
} CurrentTransformerCalibrationSetting;

typedef struct
{
    uint16_t voltage;
    uint16_t frequency;
    uint16_t gain;
    CurrentTransformerCalibrationSetting cts[3];
} EnergyICCalibrationSettings;

typedef struct
{
    EnergyICCalibrationSettings energyCalibrations[2];
    CurrentTransformerCalibrationSetting ctCalibration[3];
} ApplicationSettings;

#endif