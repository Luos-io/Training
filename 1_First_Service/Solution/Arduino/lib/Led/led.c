#include "led.h"
#include "Arduino.h"

void Led_MsgHandler(service_t *service, msg_t *msg);

void Led_Init(void)
{

    revision_t revision = {.major = 1, .minor = 0, .build = 0};
    Luos_CreateService(Led_MsgHandler, STATE_TYPE, "led", revision);

    pinMode(LED_BUILTIN, OUTPUT);
}

void Led_Loop(void) {}

void Led_MsgHandler(service_t *service, msg_t *msg)
{
    if (msg->header.cmd == IO_STATE)
    {
        if (msg->data[0] == 0)
        {
            digitalWrite(LED_BUILTIN, false);
        }
        else
        {
            digitalWrite(LED_BUILTIN, true);
        }
    }
}
