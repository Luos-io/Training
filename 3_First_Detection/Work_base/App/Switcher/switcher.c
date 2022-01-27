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
}
/******************************************************************************
 * @brief loop must be call in project loop
 * @param None
 * @return None
 ******************************************************************************/
void Switcher_Loop(void)
{

}
/******************************************************************************
 * @brief Msg Handler call back when a msg receive for this service
 * @param Service destination
 * @param Msg receive
 * @return None
 ******************************************************************************/
static void Switcher_MsgHandler(service_t *service, msg_t *msg)
{

}