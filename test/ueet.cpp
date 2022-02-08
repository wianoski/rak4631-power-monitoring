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

char outByte[20] = "testtesttest";
int led = 6;
char inByte;
int i = 0;

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    Serial.println("SPI Tst");
}
void loop()
{
    for (i = 0; outByte[i] != '\r'; i++) // send and receive the bytes of the string
    {
        inByte = SPI.transfer(outByte[i]);
        Serial.write(inByte);
    }

    Serial.println();

    delay(1000);
    Serial.println("loop");
    delay(1000);
}