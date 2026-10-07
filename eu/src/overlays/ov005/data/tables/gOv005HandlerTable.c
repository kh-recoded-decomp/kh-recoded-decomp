#include "nitro/types.h"

extern void ScriptCmd_ApplyVectorOperation(void);

void (*gOv005HandlerTable[1])(void) = {
    ScriptCmd_ApplyVectorOperation,
};
