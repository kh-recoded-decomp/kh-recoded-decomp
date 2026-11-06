#include "nitro/types.h"

extern u32 gArrowPromptWork;
extern u32 GetFieldSceneManager(void);
extern u32 GetSceneTagTracker(void);
extern void ClearTileTableRect(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);
extern u32 FindActiveRecordById(u32 handle, u32 tag);
extern void InvokeCallback40(u32 handle, u32 value);

void HideArrowPromptTimedCounters(void)
{
    u8 *context;
    u32 group;
    u32 handle;
    u32 value;

    context = (u8 *)gArrowPromptWork;
    group = GetFieldSceneManager();
    handle = GetSceneTagTracker();
    *(u32 *)(context + 8) = 0;
    ClearTileTableRect(group, 0xb, 0xe, 0, 4, 2);
    value = FindActiveRecordById(handle, 0x134);
    InvokeCallback40(handle, value);
    value = FindActiveRecordById(handle, 0x12e);
    InvokeCallback40(handle, value);
}
