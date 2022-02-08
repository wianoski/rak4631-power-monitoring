#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <bluefruit.h>
#include <freertos/Source/include/FreeRTOS.h>
#include <freertos/Source/include/task.h>
#include <freertos/Source/include/queue.h>

#define WISBLOCK_ENERGY_MOSI WB_SPI_MOSI
#define WISBLOCK_ENERGY_MISO WB_SPI_MISO
#define WISBLOCK_ENERGY_CLK WB_SPI_CLK
#define WISBLOCK_ENERGY_CS_1 WB_IO4
#define WISBLOCK_ENERGY_CS_2 WB_IO5

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    SPI.begin();
    pinMode(WISBLOCK_ENERGY_CS_1, OUTPUT);
    pinMode(WISBLOCK_ENERGY_CS_2, OUTPUT);
}

void loop()
{
}