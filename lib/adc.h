#pragma once
#ifndef __ADC__H_
#define __ADC__H_

#include <stdio.h>

#include "driver/adc.h"
#include "esp_system.h"
#include <string.h>
#include "cJSON.h"
#include "Timestamp.h"
// #include "queueService.h"
void adc_task(void *pvParameters);

#endif
