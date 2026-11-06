#include "nitro/types.h"

extern u32 SetPendingFieldValue();

u32 ScriptCmd_RequestFieldExitToScene4(s32 entry) {
    SetPendingFieldValue(3);
    *(u32 *)(entry + 0x1cc) = 0;
    return 3;
}
