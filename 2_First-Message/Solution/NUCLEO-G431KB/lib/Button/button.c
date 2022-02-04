#include "button.h"
#include "gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/
void Button_Init(void)
{
    revision_t revision = {1, 0, 0};
    Luos_CreateService(Button_MsgHandler, STATE_TYPE, "button", revision);
}

Button_Loop()
{
    msg_t *msg;
    while (Luos_ReadMsg(button_service, &msg) == SUCCEED)
    {
    if ((msg->header.cmd == IO_STATE)||(msg->header.cmd == UNKNOW)
    {
            // fill the message infos
            msg_t pub_msg;
            pub_msg.header.cmd = IO_STATE;
            pub_msg.header.target_mode = IDACK;
            pub_msg.header.target = msg->header.source;
            pub_msg.header.size = sizeof(char); // 1 byte
            pub_msg.data[0] = HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin);
            Luos_SendMsg(service, &pub_msg);
    }
    }
}
