#include "http.h"
#include <esp_http_client.h>

char *payload;
// connect_to_wifi();
const struct addrinfo hints = {
    .ai_family = AF_INET,
    .ai_socktype = SOCK_STREAM,
};
// Function to copy the string


// hàm ok, đã tự giải phóng các biến nội bộ.
void sendToServer(char *payload)

{

    struct addrinfo *res;
    struct in_addr *addr;
    int s, r;

    char *request = malloc(700);

    int err = getaddrinfo(WEB_SERVER, WEB_PORT, &hints, &res);
    if (err != 0 || res == NULL)
    {
        ESP_LOGE(TAG, "DNS lookup failed err=%d res=%p", err, res);
        // vTaskDelay(10 / portTICK_PERIOD_MS);

        //  close(s);
        return;
    }

    addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
    // ESP_LOGI(TAG, "DNS lookup succeeded. IP=%s", inet_ntoa(*addr));

    s = socket(res->ai_family, res->ai_socktype, 0);
    if (s < 0)
    {
        ESP_LOGE(TAG, "... Failed to allocate socket.");

        close(s);

        // if (payload != NULL)
        // {
        //     free(payload);
        //     payload = NULL;
        // }

        freeaddrinfo(res);
        // vTaskDelay(1 / portTICK_PERIOD_MS);
        return;
    }

    if (connect(s, res->ai_addr, res->ai_addrlen) != 0)
    {
        ESP_LOGE(TAG, "... socket connect failed errno=%d", errno);
        //  vTaskDelay(1 / portTICK_PERIOD_MS);
        close(s);

        freeaddrinfo(res);

        if (request != NULL)
        {
            free(request);
            request = NULL;
        }

        return;
    }

    char *body = payload;

    int request_len = sprintf(request, REQUEST_FORMAT, WEB_PATH, WEB_SERVER, WEB_PORT, strlen(request) + strlen(body));

    char *request_w_body = strcat(request, body);

    if (write(s, request_w_body, strlen(request_w_body)) < 0)
    {
        ESP_LOGE(TAG, "... socket send failed");

        close(s);

        // try to free all;
        // if (body != NULL)
        // {
        //     free(body);
        //     body = NULL;
        // }
        freeaddrinfo(res);

        if (request != NULL)
        {
            free(request);
            request = NULL;
        }

        vTaskDelay(2 / portTICK_PERIOD_MS);
        return;
    }

    vTaskDelay(1 / portTICK_PERIOD_MS);
    close(s);
    freeaddrinfo(res);

    // if (body != NULL)
    // {
    //     free(body);
    //     body = NULL;
    // }

    if (request != NULL)
    {
        free(request);
        request = NULL;
    }
};

void http_get_task(void *pvParameters)
{

    // char txbuff[4000];

    if (!queue)
        queue = xQueueCreate(ITEMS_NUM, ITEM_SIZE);

   

    char rxbuff[700];
   
    while (1)
    {
        if (xQueueReceive(queue, &rxbuff, (TickType_t)1)) {
            sendToServer(rxbuff);
        };
    };

}



// đã giải phóng bộ nhớ cho mọi biến nội bộ.
char *createJsonBody(int timestamp, char *pir_id, char *pirs_vol)
{
    printf("Creating json with %s timestamp: %d\n", pir_id, timestamp);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "timestamp", timestamp);
    // cJSON_AddStringToObject(root, "timestamp", timestamp);
    cJSON_AddStringToObject(root, "pir", pir_id);
    cJSON_AddStringToObject(root, "vol", pirs_vol);

    char *out = cJSON_Print(root);
    cJSON_Delete(root);
    return (char*)out;
}

// Function to copy the string
char *copyString(char s[], int len)
{
    //     char *s2;

    //     s2 = (char *)malloc(len + 1);
    //     strcpy(s2, s);
    //     return (char *)s2;

    return strdup(s);
}
