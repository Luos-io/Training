/******************************************************************************
 * @file Switcher
 * @brief training on detection that turn on the LED when Button is push
 * @author Luos
 * @version 0.0.0
 ******************************************************************************/
#include <Arduino.h>
#include "Switcher.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum
{
    SWITCHER_APP = LUOS_LAST_TYPE
} App_type_t;
/*******************************************************************************
 * Variables
 ******************************************************************************/
service_t *switcher_app; // This will be our blinker service

uint16_t ID_Led = 0;
uint16_t ID_Button = 0;
uint8_t ButtonValue = 0;
uint8_t Prev_ButtonValue = 0;
uint32_t ActuelTime;
/*******************************************************************************
 * Function
 ******************************************************************************/
static void Switcher_MsgHandler(service_t *service, msg_t *msg);
/******************************************************************************
 * @brief init must be call in project init
 * @param None
 * @return None
 ******************************************************************************/
void Switcher_Init(void)
{
    revision_t revision = {.major = 1, .minor = 0, .build = 0};
    switcher_app = Luos_CreateService(Switcher_MsgHandler, SWITCHER_APP, "Switcher", revision);
    Luos_Detect(switcher_app);
    ActuelTime = LuosHAL_GetSystick();
}
/******************************************************************************
 * @brief loop must be call in project loop
 * @param None
 * @return None
 ******************************************************************************/
void Switcher_Loop(void)
{
    msg_t pub_msg;
    if (Luos_IsNodeDetected() == true) // Topology detection Finish
    {
        if ((LuosHAL_GetSystick() - ActuelTime) > 10) // check the loop every 0ms
        {
            ActuelTime = LuosHAL_GetSystick();
            if (ID_Button != 0)
            {
                pub_msg.header.cmd = IO_STATE;
                pub_msg.header.target_mode = ID;
                pub_msg.header.target = ID_Button;
                pub_msg.header.size = 0;
                Luos_SendMsg(switcher_app, &pub_msg);
            }
            if (ID_Led != 0)
            {
                if (ButtonValue != Prev_ButtonValue)
                {
                    Prev_ButtonValue = ButtonValue;

                    pub_msg.header.cmd = IO_STATE;
                    pub_msg.header.target_mode = ID;
                    pub_msg.header.target = ID_Led;
                    pub_msg.header.size = 1;
                    pub_msg.data[0] = ButtonValue;
                    Luos_SendMsg(switcher_app, &pub_msg);
                }
            }
        }
    }
}
/******************************************************************************
 * @brief Msg Handler call back when a msg receive for this service
 * @param Service destination
 * @param Msg receive
 * @return None
 ******************************************************************************/
static void Switcher_MsgHandler(service_t *service, msg_t *msg)
{
    if (msg->header.cmd == END_DETECTION)
    {
        ID_Led = RoutingTB_IDFromAlias("led");
        ID_Button = RoutingTB_IDFromAlias("button");
    }
    else if ((msg->header.cmd == IO_STATE) && (msg->header.source == ID_Button))
    {
        ButtonValue = msg->data[0];
    }
}