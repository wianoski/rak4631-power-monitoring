#ifndef DYCODEX_POWTRAX_SETTINGS_READER_H
#define DYCODEX_POWTRAX_SETTINGS_READER_H

#include "AppSettings.h"
#include <Preferences.h>

class SettingsReader
{

public:
    SettingsReader();
    ~SettingsReader() {}

    bool load(ApplicationSettings *appSettings);
    bool reset(ApplicationSettings *appSettings);
    bool save(ApplicationSettings *appSettings);
    bool begin();
private:
    Preferences *_prefs;
};

extern SettingsReader AppSettingsReader;

#endif