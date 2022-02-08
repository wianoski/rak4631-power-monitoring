#ifndef DYCODEX_ENERGY_BYTES_SERIALIZER_H
#define DYCODEX_ENERGY_BYTES_SERIALIZER_H

#include "EnergyReadings.h"
#include <Arduino.h>

#define ENERGY_BYTES_SERIALIZED_SIZE 12

/*
0,0 = 0 * 3 + 0 + 1 = 1
0,1 = 0 * 3 + 1 + 1 = 2
0,2 = 0 * 3 + 2 + 1 = 3
1,0 = 1 * 3 + 0 + 1 = 4
1,1 = 1 * 3 + 1 + 1 = 5
1,2 = 1 * 3 + 2 + 1 = 6
*/
size_t channelNumber(size_t numIc, size_t numChannel)
{
    return numIc * 3 + numChannel + 1;
}

class EnergyBytesSerializer
{
public:
    static void serializeEnergy(EnergyReadings *readings, size_t numIc, size_t numChannel, uint8_t *output)
    {
        uint8_t serialized[ENERGY_BYTES_SERIALIZED_SIZE] = {0};

        uint8_t channel = channelNumber(numIc, numChannel);
        // uint8_t channel = numChannel;
        uint16_t voltage = readings[numIc].voltage * 10;
        uint8_t frequency = readings[numIc].frequency;
        uint16_t current = readings[numIc].current[numChannel] * 10;
        uint16_t realPower = readings[numIc].realPower[numChannel] * 10;
        uint16_t vaPower = readings[numIc].vaPower[numChannel] * 10;
        uint16_t powFactor = readings[numIc].powerFactor[numChannel] * 10;

        size_t lenChannel = sizeof(channel);
        size_t lenVoltage = sizeof(voltage);
        size_t lenFreq = sizeof(frequency);
        size_t lenCurrent = sizeof(current);
        size_t lenrealPower = sizeof(realPower);
        size_t lenvaPower = sizeof(vaPower);
        size_t lenpowFactor = sizeof(powFactor);
        size_t vessel = {0};

        memcpy(serialized, &channel, lenChannel);
        vessel += lenChannel;
        memcpy(serialized + vessel, &voltage, lenVoltage);
        vessel += lenVoltage;
        memcpy(serialized + vessel, &frequency, lenFreq);
        vessel += lenFreq;
        memcpy(serialized + vessel, &current, lenCurrent);
        vessel += lenCurrent;
        memcpy(serialized + vessel, &realPower, lenrealPower);
        vessel += lenrealPower;
        memcpy(serialized + vessel, &vaPower, lenvaPower);
        vessel += lenvaPower;
        memcpy(serialized + vessel, &powFactor, lenpowFactor);
        //need to validation
        memcpy(output, serialized, ENERGY_BYTES_SERIALIZED_SIZE);
    }
};

#endif