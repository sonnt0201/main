#ifndef __ADC__H_
#define __ADC__H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_system.h"
#include <string.h>
#include "cJSON.h"
#include "Timestamp.h"
#include "freertos/queue.h"
void adc_task(void *pvParameters);

#endif
