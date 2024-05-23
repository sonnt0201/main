
#include "adc.h"
// Task handler function

QueueHandle_t queue;

void adc_task(void *pvParameters)
{
    start: 
  
    // QueueHandle_t adcQueue = (QueueHandle_t)pvParameters;
    if (!queue)
        queue = xQueueCreate(ITEMS_NUM, ITEM_SIZE);
    printf("Queue Created !\n");
    // Configure ADC1 channels for full range with 11 dB attenuation
    adc1_config_width(ADC_WIDTH_BIT_12); // Set ADC resolution to 12 bits

    // Configure ADC1 channels for full range with 11 dB attenuation
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11); // GPIO 39, max input ~3.9V
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11); // GPIO 32, max input ~3.9V
    adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11); // GPIO 33, max input ~3.9V
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); // GPIO 34, max input ~3.9V
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11); // GPIO 35, max input ~3.9V

    // Loop indefinitely
    // Read ADC value from channel 4
    char StrPir0[600]="";

    char StrPir1[600]="";

    char StrPir2[600]="";

    char StrPir3[600]="";

    char StrPir4[600]="";

    // memset(StrPir0, 0, 600);
    // memset(StrPir1, 0, 600);
    // memset(StrPir2, 0, 600);
    // memset(StrPir3, 0, 600);
    // memset(StrPir4, 0, 600);

    TickType_t GetTick = xTaskGetTickCount();
    while (1)
    {

        time_t timestamp = get_current_timestamp();
        for (int i = 0; i < 100; i++)
        {
            int raw_data0 = adc1_get_raw(ADC1_CHANNEL_3);
            sprintf(&StrPir0[i * 5], "%04d%c", raw_data0, (i != 99 ? '_' : '\0'));
            int raw_data1 = adc1_get_raw(ADC1_CHANNEL_4);
            sprintf(&StrPir1[i * 5], "%04d%c", raw_data1, (i != 99 ? '_' : '\0'));
            int raw_data2 = adc1_get_raw(ADC1_CHANNEL_5);
            sprintf(&StrPir2[i * 5], "%04d%c", raw_data2, (i != 99 ? '_' : '\0'));
            int raw_data3 = adc1_get_raw(ADC1_CHANNEL_6);
            sprintf(&StrPir3[i * 5], "%04d%c", raw_data3, (i != 99 ? '_' : '\0'));
            int raw_data4 = adc1_get_raw(ADC1_CHANNEL_7);
            sprintf(&StrPir4[i * 5], "%04d%c", raw_data4, (i != 99 ? '_' : '\0'));
            // Delay for 10 ms

            vTaskDelay(pdMS_TO_TICKS(10));
            // vTaskDelayUntil(&GetTick,10);
        }
        /* code */
        // printf("{Time:%ld\npir0:%s\npir1:%s\npir2:%spir3:%s\npir4:\n%s}",(long)timestamp,StrPir0,StrPir1,StrPir2,StrPir3,StrPir4);
        // printf("pir0 %s\n",StrPir0);
        // printf("pir1 %s\n",StrPir1);
        // printf("pir2 %s\n",StrPir2);
        // printf("pir3 %s\n",StrPir3);
        // printf("pir4 %s\n",StrPir4);

        // cJSON *root = cJSON_CreateObject();
        // cJSON_AddNumberToObject(root, "timestamp", timestamp);
        // cJSON

        // start to push to queue
        char *begin = Q_BEGIN_VAL;
        xQueueSend(queue, (void *)begin, (TickType_t)0);

        char *time = (char *)malloc(11);
        // char* time = "1234567890";
        char *ii = itoa(timestamp, time, 10);

        xQueueSend(queue, (void *)time, (TickType_t)0);

        ii = NULL;

        xQueueSend(queue, StrPir0, (TickType_t)0);
        xQueueSend(queue, StrPir1, (TickType_t)0);
        xQueueSend(queue, StrPir2, (TickType_t)0);
        xQueueSend(queue, StrPir3, (TickType_t)0);
        xQueueSend(queue, StrPir4, (TickType_t)0);

        //  xQueueSend(queue, "pir0", (TickType_t)0);
        //  xQueueSend(queue, "pir1", (TickType_t)0);
        //  xQueueSend(queue, "pir2", (TickType_t)0);
        //  xQueueSend(queue, "pir3", (TickType_t)0);
        //  xQueueSend(queue, "pir4", (TickType_t)0);

        // cJSON *records = cJSON_CreateArray();
        // cJSON_AddItemToObject(root, "records", records);

        // // Tạo mảng records cho mỗi PIR
        // cJSON_AddItemToArray(records, cJSON_CreateObject());
        // cJSON_AddItemToObject(cJSON_GetArrayItem(records, 0), "pir", cJSON_CreateString("0"));
        // cJSON_AddItemToObject(cJSON_GetArrayItem(records, 0), "vol", cJSON_CreateString(StrPir0));

        // cJSON_AddItemToArray(records, cJSON_CreateObject());
        // cJSON_AddItemToObject(cJSON_GetArrayItem(records, 1), "pir", cJSON_CreateString("1"));
        // cJSON_AddItemToObject(cJSON_GetArrayItem(records, 1), "vol", cJSON_CreateString(StrPir1));

        // cJSON_AddItemToArray(records, cJSON_CreateObject());
        // cJSON_AddItemToObject(cJSON_GetArrayItem(records, 2), "pir", cJSON_CreateString("2"));
        // cJSON_AddItemToObject(cJSON_GetArrayItem(records, 2), "vol", cJSON_CreateString(StrPir2));

        // cJSON_AddItemToArray(records, cJSON_CreateObject());
        // cJSON_AddItemToObject(cJSON_GetArrayItem(records, 3), "pir", cJSON_CreateString("3"));
        // cJSON_AddItemToObject(cJSON_GetArrayItem(records, 3), "vol", cJSON_CreateString(StrPir3));

        // cJSON_AddItemToArray(records, cJSON_CreateObject());
        // cJSON_AddItemToObject(cJSON_GetArrayItem(records, 4), "pir", cJSON_CreateString("4"));
        // cJSON_AddItemToObject(cJSON_GetArrayItem(records, 4), "vol", cJSON_CreateString(StrPir4));

        // // In chuỗi JSON
        // char *json_string = cJSON_Print(root);

        // // Gửi giá trị ADC vào hàng đợi
        // xQueueSend(queue, &root, portMAX_DELAY);
        // printf("%s\n", json_string);

        // sprintf(txbuff, json_string);

        printf("Queue appended !: %d\n", uxQueueMessagesWaiting(queue));



        if (uxQueueMessagesWaiting(queue) > 21) {
            
            xQueueReset(queue);

            free(ii);
            free(time);
            ii = "";
            time = "";

            goto start;
        }

        // // Giải phóng bộ nhớ
        // cJSON_Delete(root);
        // free(json_string);

        // free(StrPir0);
        // free(StrPir1);
        // free(StrPir2);
        // free(StrPir3);
        // free(StrPir4);
    };
};