#include <Arduino.h>
#include "button.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BTN_PIN 8

/*******************************************************************************
 * Variable
 ******************************************************************************/
service_t *button_service;
/*******************************************************************************
 * Functions
 ******************************************************************************/
void Button_Init(void)
{
    revision_t revision = {1, 0, 0};
    button_service = Luos_CreateService(0, STATE_TYPE, "button", revision);
    pinMode(BTN_PIN, INPUT);
}

void Button_Loop(void)
{
    msg_t *msg;
    while (Luos_ReadMsg(button_service, &msg) == SUCCEED)
    {
        if ((msg->header.cmd == IO_STATE) || (msg->header.cmd == UNKNOWN_CMD))
        {
            // fill the message infos
            msg_t pub_msg;
            pub_msg.header.cmd = IO_STATE;
            pub_msg.header.target_mode = IDACK;
            pub_msg.header.target = msg->header.source;
            pub_msg.header.size = sizeof(char); // 1 byte
            pub_msg.data[0] = digitalRead(BTN_PIN);
            Luos_SendMsg(button_service, &pub_msg);
        }
    }
}
