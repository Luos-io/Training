#include "switcher.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
enum // Custom type list
{
    SWITCHER_APP = LUOS_LAST_TYPE
};

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
