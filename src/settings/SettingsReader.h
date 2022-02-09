#ifndef DYCODEX_POWTRAX_SETTINGS_READER_H
#define DYCODEX_POWTRAX_SETTINGS_READER_H

#include "AppSettings.h"

#define ENERGY_GAIN 0
#define ENERGY_CAL 27961

class SettingsReader
{

public:
    SettingsReader();
    ~SettingsReader() {}

    bool load(ApplicationSettings *appSettings);
    bool reset(ApplicationSettings *appSettings);
    bool save(ApplicationSettings *appSettings);
    bool begin();
};

extern SettingsReader AppSettingsReader;

#endif