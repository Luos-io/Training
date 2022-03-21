#include <Arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "luos_engine.h"
#include "led.h"
//#include "button.h"
#include "switcher.h"

#ifdef __cplusplus
}
#endif

/******************************************************************************
 * @brief Setup ardiuno
 * @param None
 * @return None
 ******************************************************************************/
void setup()
{
    Luos_Init();
    Led_Init();
    // Button_Init();
    Switcher_Init();
}
/******************************************************************************
 * @brief Loop Arduino
 * @param None
 * @return None
 ******************************************************************************/
void loop()
{
    Luos_Loop();
    Led_Loop();
    // Button_Loop();
    Switcher_Loop();
}
