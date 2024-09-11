
#include "adc.h"
// Task handler function
#include "http.h"

QueueHandle_t queue;



void adc_task(void *pvParameters)
{

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

    // khai báo cấp bộ nhớ ở ngoài vòng while => cấp 1 lần và không cần giải phóng.
    char StrPir0[600] = "";

    // khai báo cấp bộ nhớ ở ngoài vòng while => cấp 1 lần và không cần giải phóng.
    char StrPir1[600] = "";

    // khai báo cấp bộ nhớ ở ngoài vòng while => cấp 1 lần và không cần giải phóng.
    char StrPir2[600] = "";

    // khai báo cấp bộ nhớ ở ngoài vòng while => cấp 1 lần và không cần giải phóng.
    char StrPir3[600] = "";

    // khai báo cấp bộ nhớ ở ngoài vòng while => cấp 1 lần và không cần giải phóng.
    char StrPir4[600] = "";

    // memset(StrPir0, 0, 600);
    // memset(StrPir1, 0, 600);
    // memset(StrPir2, 0, 600);
    // memset(StrPir3, 0, 600);
    // memset(StrPir4, 0, 600);

    

    TickType_t GetTick = xTaskGetTickCount();
    while (1)
    {
        // char* StrPir0 = malloc(600);
        // char* StrPir1 = malloc(600);
        // char* StrPir2 = malloc(600);
        // char* StrPir3 = malloc(600);
        // char* StrPir4 = malloc(600);

        if (queue == NULL)
            xQueueCreate(ITEMS_NUM, ITEM_SIZE);

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

        // // khai báo trong vòng while, phải giải phóng bộ nhớ ở cuối vòng while
        // char *time = (char *)malloc(11);
        // // char* time = "1234567890";
        // char *ii = itoa(timestamp, time, 10);

        // hàm sendToServer không giải phóng bộ nhớ cho tham số truyền vào. chỉ giải phóng bộ nhớ cho các biến nội bộ
        // sendToServer("hello from client !");

        // char begin[1] = Q_BEGIN_VAL;
        // xQueueSend(queue, begin, (TickType_t) 0);


        // phải giải phóng, đã giải phóng ở dòng dưới
        char *jsonStr0 = createJsonBody(timestamp, "0", StrPir0);
        // sendToServer(jsonStr0);
        xQueueSend(queue, (void *)jsonStr0, (TickType_t)0);
        free(jsonStr0);
        jsonStr0 = NULL;

        char *jsonStr1 = createJsonBody(timestamp, "1", StrPir1);
        // sendToServer(jsonStr1);
        xQueueSend(queue, (void *)jsonStr1, (TickType_t)0);

        free(jsonStr1);
        jsonStr1 = NULL;

        char *jsonStr2 = createJsonBody(timestamp, "2", StrPir2);
        // sendToServer(jsonStr2);
         xQueueSend(queue, (void *)jsonStr2, (TickType_t)0);
        free(jsonStr2);
        jsonStr2 = NULL;

        char *jsonStr3 = createJsonBody(timestamp, "3", StrPir3);
        // sendToServer(jsonStr3);
         xQueueSend(queue, (void *)jsonStr3, (TickType_t)0);
        free(jsonStr3);
        jsonStr3 = NULL;

        char *jsonStr4 = createJsonBody(timestamp, "4", StrPir4);
        // sendToServer(jsonStr4);
         xQueueSend(queue, (void *)jsonStr4, (TickType_t)0);
        free(jsonStr4);
        jsonStr4 = NULL;
        // if (jsonStr != NULL)
        // printf("%s\n", jsonStr);

        // giải phóng

        // sendToServer(jsonStr);

        // if (time != NULL)
        // {
        //     free(time);
        //     time = NULL;
        // }
        // if (ii != NULL)
        // {
        //     free(ii);
        //     ii = NULL;
        // }
    };
};