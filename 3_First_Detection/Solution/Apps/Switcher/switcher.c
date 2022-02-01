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
service_t *switcher_app; // This will be our switcher service

uint16_t ID_Led = 0;
uint16_t ID_Button = 0;
uint32_t ActualTime;

/*******************************************************************************
 * Functions
 ******************************************************************************/
void Switcher_MsgHandler(service_t *service, msg_t *msg)
{
  if (msg->header.cmd == END_DETECTION)
  {
    ID_Led = RoutingTB_IDFromAlias("led");
    ID_Button = RoutingTB_IDFromAlias("button");
  }
  else if ((msg->header.cmd == IO_STATE) &&
           (msg->header.source == ID_Button))
  {
    if (ID_Led != 0)
    {
      msg_t pub_msg;
      pub_msg.header.cmd = IO_STATE;
      pub_msg.header.target_mode = ID;
      pub_msg.header.target = ID_Led;
      pub_msg.header.size = 1;
      pub_msg.data[0] = msg->data[0];
      Luos_SendMsg(switcher_app, &pub_msg);
    }
  }
}

void Switcher_Init(void)
{
  revision_t revision = {1, 0, 0};
  switcher_app = Luos_CreateService(Switcher_MsgHandler, SWITCHER_APP,
                                    "Switcher", revision);
  Luos_Detect(switcher_app);
  ActualTime = LuosHAL_GetSystick();
}

void Switcher_Loop(void)
{
  msg_t pub_msg;
  if (Luos_IsNodeDetected() == true) // Topology detection Finish
  {
    // ask button value every 10ms
    if ((Luos_GetSystick() - ActualTime) > 10)
    {
      ActualTime = LuosHAL_GetSystick();
      if (ID_Button != 0)
      {
        pub_msg.header.cmd = IO_STATE;
        pub_msg.header.target_mode = ID;
        pub_msg.header.target = ID_Button;
        pub_msg.header.size = 0;
        Luos_SendMsg(switcher_app, &pub_msg);
      }
    }
  }
}
