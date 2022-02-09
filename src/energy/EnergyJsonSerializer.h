#ifndef DYCODEX_ENERGY_JSON_SERIALIZER
#define DYCODEX_ENERGY_JSON_SERIALIZER

#include "EnergyReadings.h"
#include <Arduino.h>
#include <ArduinoJson.h>

class EnergyJsonSerializer
{
public:
    static String serializeEnergy(EnergyReadings *readings, size_t numIcs)
    {
        DynamicJsonDocument doc(1024);
        JsonArray array = doc.createNestedArray("readings");

        for (int num = 0; num < numIcs; num++)
        {
            JsonObject root = array.createNestedObject();

            root["voltage"] = readings[num].voltage;
            root["temperature"] = readings[num].temperature;
            root["frequency"] = readings[num].frequency;

            for (int i = 0; i < ENERGYIC_NUM_INPUTS; i++)
            {
                root["line_volt_" + String(i)] = readings[num].lineVoltage[i];
                root["line_current_" + String(i)] = readings[num].current[i];
                root["real_power_" + String(i)] = readings[num].realPower[i];
                root["va_power_" + String(i)] = readings[num].vaPower[i];
                root["power_factor_" + String(i)] = readings[num].powerFactor[i];
            }

            root["sys0"] = readings[num].sys0;
            root["sys1"] = readings[num].sys1;
            root["en0"] = readings[num].en0;
            root["en1"] = readings[num].en1;
        }

        String result;
        serializeJson(doc, result);

        return result;
    }

};

#endif