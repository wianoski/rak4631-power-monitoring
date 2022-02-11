#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <bluefruit.h>
#include <freertos/Source/include/FreeRTOS.h>
#include <freertos/Source/include/task.h>
#include <freertos/Source/include/queue.h>
#include <ATM90E32.h>
#include <littlefs/lfs.h>

#include "settings/AppSettings.h"
#include "settings/SettingsReader.h"
#include "energy/EnergyConstants.h"
#include "energy/EnergyReadings.h"
#include "energy/EnergyJsonSerializer.h"

#define WISBLOCK_ENERGY_MOSI WB_SPI_MOSI
#define WISBLOCK_ENERGY_MISO WB_SPI_MISO
#define WISBLOCK_ENERGY_CLK WB_SPI_CLK
#define WISBLOCK_ENERGY_CS_1 WB_IO4
#define WISBLOCK_ENERGY_CS_2 WB_IO3

ApplicationSettings *settings;

const uint8_t energyMonitorCS[2] = {SS, WISBLOCK_ENERGY_CS_2};
ATM90E32 *energyMonitorIc[ENERGYIC_NUM_ICS] = {
    new ATM90E32(),
    new ATM90E32(),
};

EnergyReadings readings[2] = {
    {},
    {},
};

volatile bool isReadingSensor = false;
void energyReading(volatile bool *isReadingSensor)
{
    *isReadingSensor = true;
    for (int ic = 0; ic < ENERGYIC_NUM_ICS; ic++)
    {
        readings[ic].sys0 = energyMonitorIc[ic]->GetSysStatus0();
        readings[ic].sys1 = energyMonitorIc[ic]->GetSysStatus1();
        readings[ic].en0 = energyMonitorIc[ic]->GetMeterStatus0();
        readings[ic].en1 = energyMonitorIc[ic]->GetMeterStatus1();

        Serial.println("Sys Status 1: S0:0x" + String(readings[ic].sys0, HEX) + " S1:0x" + String(readings[ic].sys1, HEX));
        Serial.println("Meter Status 1: E0:0x" + String(readings[ic].en0, HEX) + " E1:0x" + String(readings[ic].en1, HEX));

        readings[ic].voltage = energyMonitorIc[ic]->GetLineVoltageA();
        readings[ic].frequency = energyMonitorIc[ic]->GetFrequency();
        readings[ic].temperature = energyMonitorIc[ic]->GetTemperature();

        Serial.println("Temp: " + String(readings[ic].temperature) + "C");
        Serial.println("Freq: " + String(readings[ic].frequency) + "Hz");
        Serial.println("V: " + String(readings[ic].voltage) + "V");

        readings[ic].lineVoltage[0] = energyMonitorIc[ic]->GetLineVoltageA();
        readings[ic].lineVoltage[1] = energyMonitorIc[ic]->GetLineVoltageB();
        readings[ic].lineVoltage[2] = energyMonitorIc[ic]->GetLineVoltageC();

        readings[ic].current[0] = energyMonitorIc[ic]->GetLineCurrentA();
        readings[ic].current[1] = energyMonitorIc[ic]->GetLineCurrentB();
        readings[ic].current[2] = energyMonitorIc[ic]->GetLineCurrentC();

        readings[ic].realPower[0] = energyMonitorIc[ic]->GetActivePowerA();
        readings[ic].realPower[1] = energyMonitorIc[ic]->GetActivePowerB();
        readings[ic].realPower[2] = energyMonitorIc[ic]->GetActivePowerC();

        readings[ic].vaPower[0] = energyMonitorIc[ic]->GetApparentPowerA();
        readings[ic].vaPower[1] = energyMonitorIc[ic]->GetApparentPowerB();
        readings[ic].vaPower[2] = energyMonitorIc[ic]->GetApparentPowerC();

        readings[ic].powerFactor[0] = energyMonitorIc[ic]->GetPowerFactorA();
        readings[ic].powerFactor[1] = energyMonitorIc[ic]->GetPowerFactorB();
        readings[ic].powerFactor[2] = energyMonitorIc[ic]->GetPowerFactorC();

        for (int i = 0; i < ENERGYIC_NUM_INPUTS; i++)
        {
            if (readings[ic].realPower[i] < 0)
            {
                readings[ic].current[i] *= -1;
            }

            readings[ic].current[i] *= settings->energyCalibrations[0].cts[i].currentMultiplier;
            readings[ic].realPower[i] *= settings->energyCalibrations[0].cts[i].powerMultiplier * settings->energyCalibrations->cts[i].currentMultiplier;
            readings[ic].vaPower[i] *= fabs(settings->energyCalibrations[0].cts[i].powerMultiplier * settings->energyCalibrations->cts[i].currentMultiplier);

            Serial.println(String(ic) + "_" + String(i) + ":" + String(readings[ic].current[i]) + "A");
        }
    }
    String json = EnergyJsonSerializer::serializeEnergy(readings, ENERGYIC_NUM_ICS);

    *isReadingSensor = false;
    // Serial.println(json);
}

uint32_t lastSensorRead = 0;
void setup()
{
    Serial.begin(115200);
    Wire.begin();

    pinMode(WISBLOCK_ENERGY_CS_1, OUTPUT);
    pinMode(WISBLOCK_ENERGY_CS_2, OUTPUT);
    SPI.begin();

    settings = new ApplicationSettings;

    for (int ic = 0; ic < ENERGYIC_NUM_ICS; ic++)
    {
        energyMonitorIc[ic]->begin(energyMonitorCS[ic],
                                   settings->energyCalibrations[ic].frequency,
                                   settings->energyCalibrations[ic].voltage,
                                   settings->energyCalibrations[ic].gain,
                                   settings->energyCalibrations[ic].cts[0].cal,
                                   settings->energyCalibrations[ic].cts[1].cal,
                                   settings->energyCalibrations[ic].cts[2].cal);
    }
    delay(200);
}

void loop()
{
    if (lastSensorRead == 0 || (millis() - lastSensorRead >= 10000))
    {
        energyReading(&isReadingSensor);
        lastSensorRead = millis();
    }
}