#include <stdio.h>

#include "driver/adc.h"
#include "esp_system.h"
#include <string.h>
#include "adc.h"
#include "Timestamp.h"
#include "WifiConnect.h"
#include "http.h"

void app_main()
{
    // adcQueue = xQueueCreate(10, sizeof(char *));

    // QueueHandle_t adcQueue = xQueueCreate(10, sizeof(int));
    ESP_ERROR_CHECK(nvs_flash_init());
    connect_to_wifi();
    initialize_sntp();
    // // Create ADC task

    wait_for_time();

    // // json_queue = xQueueCreate(1, JSON_STRING_SIZE);
    xTaskCreatePinnedToCore(adc_task, "adc_task", 8196, NULL, 1, NULL, 0); // Chạy task adc_task ở core 0
    xTaskCreatePinnedToCore(http_get_task, "http_post_task", 8192, NULL, 13, NULL, 1); // Chạy task http_post_task ở core 1

    // adc1_config_width(ADC_WIDTH_BIT_12); // Set ADC resolution to 12 bits

    // // Configure ADC1 channels for full range with 11 dB attenuation
    // adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11); // GPIO 39, max input ~3.9V
    // adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11); // GPIO 32, max input ~3.9V
    // adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11); // GPIO 33, max input ~3.9V
    // adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); // GPIO 34, max input ~3.9V
    // adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11); // GPIO 35, max input ~3.9V

    // // Loop indefinitely
    // // Read ADC value from channel 4
    // char StrPir0[600] = "";

    // char StrPir1[600] = "";

    // char StrPir2[600] = "";

    // char StrPir3[600] = "";

    // char StrPir4[600] = "";

    // memset(StrPir0, 0, 600);
    // memset(StrPir1, 0, 600);
    // memset(StrPir2, 0, 600);
    // memset(StrPir3, 0, 600);
    // memset(StrPir4, 0, 600);

    // TickType_t GetTick = xTaskGetTickCount();
    // while (1)
    // {

    //     time_t timestamp = get_current_timestamp();
    //     for (int i = 0; i < 100; i++)
    //     {
    //         int raw_data0 = adc1_get_raw(ADC1_CHANNEL_3);
    //         sprintf(&StrPir0[i * 5], "%04d%c", raw_data0, (i != 99 ? '_' : '\0'));
    //         int raw_data1 = adc1_get_raw(ADC1_CHANNEL_4);
    //         sprintf(&StrPir1[i * 5], "%04d%c", raw_data1, (i != 99 ? '_' : '\0'));
    //         int raw_data2 = adc1_get_raw(ADC1_CHANNEL_5);
    //         sprintf(&StrPir2[i * 5], "%04d%c", raw_data2, (i != 99 ? '_' : '\0'));
    //         int raw_data3 = adc1_get_raw(ADC1_CHANNEL_6);
    //         sprintf(&StrPir3[i * 5], "%04d%c", raw_data3, (i != 99 ? '_' : '\0'));
    //         int raw_data4 = adc1_get_raw(ADC1_CHANNEL_7);
    //         sprintf(&StrPir4[i * 5], "%04d%c", raw_data4, (i != 99 ? '_' : '\0'));
    //         // Delay for 10 ms

    //         vTaskDelay(pdMS_TO_TICKS(10));
    //         // vTaskDelayUntil(&GetTick,10);
    //     }
    //     char *time = (char *)malloc(11);
    //     // char* time = "1234567890";
    //     char *ii = itoa(timestamp, time, 10);

    //     char *jsonStr = createJsonBody(time, "0", StrPir0);
    //     sendToServer(jsonStr);
    //     // free(jsonStr);

    //     jsonStr = createJsonBody(time, "1", StrPir1);
    //     sendToServer(jsonStr);
    //     // free(jsonStr);

    //     jsonStr = createJsonBody(time, "2", StrPir2);
    //     sendToServer(jsonStr);
    //     // free(jsonStr);

    //     jsonStr = createJsonBody(time, "3", StrPir3);
    //     sendToServer(jsonStr);
    //     // free(jsonStr);

    //     jsonStr = createJsonBody(time, "4", StrPir4);
    //     sendToServer(jsonStr);
    //     // free(jsonStr);
    // }
}
