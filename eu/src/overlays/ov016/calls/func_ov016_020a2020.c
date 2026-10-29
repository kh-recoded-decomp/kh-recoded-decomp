#include "nitro/types.h"

extern u32 ScriptCmd_ReadEntityParams();
extern u32 func_ov001_0208723c();
extern void SpawnFieldObjectTree();

u32 func_ov016_020a2020(u32 messageId, u32 arg1)
{
    u32 context;
    u32 cursor;
    u8 buffer[92];

    cursor = arg1;
    ScriptCmd_ReadEntityParams(buffer, messageId, &cursor);
    context = func_ov001_0208723c();
    SpawnFieldObjectTree(context, buffer);
    return 1;
}
