#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
QueueHandle_t xQueue;

void taskQueueTest(void *pvParameters)
{
  int data = 0;
  while (1)
  {
    Serial.println("Task Queue Test");
    if (xQueueReceive(xQueue, &data, portMAX_DELAY)==pdPASS)
    {
      Serial.print("Received: ");
      Serial.println(data);
    }
    vTaskDelay(1000);
  }
};

void taskPrint(void *pvParameters){
  while(1){
    int tr;
    xQueueSend(xQueue, &tr, portMAX_DELAY);
    Serial.println("Task Print");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  xQueue = xQueueCreate(5, sizeof(int));
  if (xQueue != NULL)
  {
    xTaskCreate(taskQueueTest, "taskQueueTest", 2048, NULL, 5, NULL);
    xTaskCreate(taskPrint, "taskPrint", 2048, NULL, 5, NULL);
  }
  else
  {
    Serial.println("Queue is not created");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  // Serial.println("Hello, world!");
}