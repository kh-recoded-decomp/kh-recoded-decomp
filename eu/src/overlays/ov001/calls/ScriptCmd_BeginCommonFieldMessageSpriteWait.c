#include "nitro/types.h"

extern u32 IsCommonFieldMessageSpriteActive();
extern u32 SetFieldEntriesPaused();

u32 ScriptCmd_BeginCommonFieldMessageSpriteWait(s32 entry) {
    s32 result = IsCommonFieldMessageSpriteActive();
    if (result != 0) {
        return 1;
    }
    *(u32 *)(*(s32 *)(entry + 0x1c8) + 0x1c8) = 0;
    SetFieldEntriesPaused(1);
    return 0;
}
