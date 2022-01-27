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
service_t *switcher_app; // This will be our switcher service

/*******************************************************************************
 * Functions
 ******************************************************************************/
void Switcher_MsgHandler(service_t *service, msg_t *msg)
{
}

void Switcher_Init(void)
{
    revision_t revision = {1, 0, 0};
    switcher_app = Luos_CreateService(Switcher_MsgHandler, SWITCHER_APP, "Switcher", revision);
}

void Switcher_Loop(void)
{
}
