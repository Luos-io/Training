#include <Arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <luos.h>
#include "blinker.h"
#include "pipe.h"
#include "gate.h"


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
    Blinker_Init();
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
    Blinker_Loop();
}
