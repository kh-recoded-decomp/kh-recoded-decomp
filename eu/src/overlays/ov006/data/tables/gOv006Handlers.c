#include "nitro/types.h"

extern void ScriptCmd_CreateElevatorClass(void);
extern void ScriptCmd_CreateElevatorObject(void);

void (*gOv006Handlers[3])(void) = {
    ScriptCmd_CreateElevatorClass,
    NULL,
    ScriptCmd_CreateElevatorObject,
};
