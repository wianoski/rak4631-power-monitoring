#include "SettingsReader.h"
// #include "SPIFFS.h"
// #include "FS.h"

#define SETTINGS_FILE "/settings/settings.data"

SettingsReader::SettingsReader()
{
}

bool SettingsReader::reset(ApplicationSettings *settings)
{

    for (int count = 0; count < 2; count++)
    {
        EnergyICCalibrationSettings energyCalibration = {};
        for (int i = 0; i < 3; i++)
        {
            CurrentTransformerCalibrationSetting ct = {};
            ct.gain = ENERGY_GAIN;
            ct.cal = ENERGY_CAL;
            ct.currentMultiplier = 1.0;
            ct.powerMultiplier = 1.0;
            // sprintf(ct.name, "ct%d", i);

            energyCalibration.cts[i] = ct;
            energyCalibration.gain |= (ct.gain << (i * 2));
        }

        energyCalibration.voltage = 0;

        settings->energyCalibrations[count] = energyCalibration;
    }

    return save(settings);
}