#include "button.h"
#include "gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/
static void Button_MsgHandler(service_t *service, msg_t *msg)
{
    if ((msg->header.cmd == IO_STATE) || (msg->header.cmd == UNKNOWN_CMD))
    {
        // fill the message infos
        msg_t pub_msg;
        pub_msg.header.cmd         = IO_STATE;
        pub_msg.header.target_mode = SERVICEID;
        pub_msg.header.target      = msg->header.source;
        pub_msg.header.size        = sizeof(char);
        pub_msg.data[0]            = HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin);
        Luos_SendMsg(service, &pub_msg);
        return;
    }
}

void Button_Init(void)
{
    revision_t revision = {1, 0, 0};
    Luos_CreateService(Button_MsgHandler, STATE_TYPE, "button", revision);
}

void Button_Loop(void)
{
}
