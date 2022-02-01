/******************************************************************************
 * @file Led
 * @brief driver example a simple Led
 * @author Luos
 * @version 0.0.0
 ******************************************************************************/
#include "led.h"
#include "gpio.h"

static void Led_MsgHandler(service_t *service, msg_t *msg);

void Led_Init(void)
{
    revision_t revision = {1, 0, 0};
    Luos_CreateService(Led_MsgHandler, STATE_TYPE, "led", revision);
}

void Led_Loop(void) {}

static void Led_MsgHandler(service_t *service, msg_t *msg)
{
    if (msg->header.cmd == IO_STATE)
    {
        if (msg->data[0] == false)
        {
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, false);
        }
        else
        {
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, true);
        }
    }
}
