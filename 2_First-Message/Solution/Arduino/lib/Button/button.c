#include <Arduino.h>
#include "button.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BTN_PIN 8

/*******************************************************************************
 * Functions
 ******************************************************************************/
static void Button_MsgHandler(service_t *service, msg_t *msg)
{
    if ((msg->header.cmd == IO_STATE) || (msg->header.cmd == GET_CMD))
    {
        // fill the message infos
        msg_t pub_msg;
        pub_msg.header.cmd         = IO_STATE;
        pub_msg.header.target_mode = ID;
        pub_msg.header.target      = msg->header.source;
        pub_msg.header.size        = sizeof(char);
        pub_msg.data[0]            = digitalRead(BTN_PIN);
        Luos_SendMsg(service, &pub_msg);
        return;
    }
}

void Button_Init(void)
{
    revision_t revision = {1, 0, 0};
    Luos_CreateService(Button_MsgHandler, STATE_TYPE, "button", revision);
    pinMode(BTN_PIN, INPUT);
}

void Button_Loop(void)
{
}