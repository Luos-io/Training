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
service_t *switcher_app; // This will be our switcher service
uint16_t ID_Led    = 0;
uint16_t ID_Button = 0;
uint32_t LastAsk;

/*******************************************************************************
 * Functions
 ******************************************************************************/
void Switcher_MsgHandler(service_t *service, const msg_t *msg)
{
    if (msg->header.cmd == END_DETECTION)
    {
        search_result_t filter_result;
        RTFilter_Reset(&filter_result);             // Init your filter.
                                                    // Now your filter_result have the entire routing table. #nofilter ;)
        RTFilter_Alias(&filter_result, "led");      // Filter your filter_result only keep the services with the alias "led"
        ID_Led = filter_result.result_table[0]->id; // recover the first service SERVICEID with alias "led"

        RTFilter_Reset(&filter_result); // Reset your filter.
        RTFilter_Alias(&filter_result, "button");
        ID_Button = filter_result.result_table[0]->id;
    }
    else if ((msg->header.cmd == IO_STATE) && (msg->header.source == ID_Button))
    {
        // Command the led accordingly to the button message
        if (ID_Led > 0)
        {
            msg_t pub_msg;
            pub_msg.header.cmd         = IO_STATE;
            pub_msg.header.target_mode = SERVICEID;
            pub_msg.header.target      = ID_Led; // configure the target to be our led service SERVICEID
            pub_msg.header.size        = 1;
            pub_msg.data[0]            = msg->data[0];
            Luos_SendMsg(switcher_app, &pub_msg);
        }
    }
}

void Switcher_Init(void)
{
    revision_t revision = {1, 0, 0};
    switcher_app        = Luos_CreateService(Switcher_MsgHandler, SWITCHER_APP, "Switcher", revision);
    Luos_Detect(switcher_app);
    LastAsk = Luos_GetSystick();
}

void Switcher_Loop(void)
{
    msg_t pub_msg;
    if (Luos_IsDetected() == true) // Topology detection Finish
    {
        // ask button value every 10ms
        if ((Luos_GetSystick() - LastAsk) > 10)
        {
            LastAsk = Luos_GetSystick();
            if (ID_Button != 0)
            {
                pub_msg.header.cmd         = IO_STATE;
                pub_msg.header.target_mode = SERVICEID;
                pub_msg.header.target      = ID_Button;
                pub_msg.header.size        = 0;
                Luos_SendMsg(switcher_app, &pub_msg);
            }
        }
    }
}
