#ine "SettingsReader.h"
#include "SPIFFS.h"
#include "FS.h"

#define SETTINGS_NAMESPACE "settings"

SettingsReader::SettingsReader()
{
}

SettingsReader::load(ApplicationSettings *settings)
{
    size_t settingsSize = sizeof(ApplicationSettings);
    char buffer[settingsSize] = {0};
    size_t readBytes = _prefs->getBytes(SETTINGS_NAMESPACE, (void *)buffer, settingsSize);
    Serial.printf("Read %d/%d\r\n", readBytes, settingsSize);
}