#include <Arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <luos.h>
#include "pipe.h"
#include "gate.h"
#include "button.h"


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
    Pipe_Init();
    Gate_Init();
    Button_Init();
}
/******************************************************************************
 * @brief Loop Arduino
 * @param None
 * @return None
 ******************************************************************************/
void loop()
{
    Luos_Loop();
    Pipe_Loop();
    Gate_Loop();
    Button_Loop();
}
