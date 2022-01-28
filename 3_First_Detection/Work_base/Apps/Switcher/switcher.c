#include <Arduino.h>
#include "switcher.h"

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

/*******************************************************************************
 * Functions
 ******************************************************************************/
void Switcher_MsgHandler(service_t *service, msg_t *msg)
{
}

void Switcher_Init(void)
{
    revision_t revision = {1, 0, 0};
    Luos_CreateService(Switcher_MsgHandler, SWITCHER_APP, "Switcher", revision);
}

void Switcher_Loop(void)
{
}
