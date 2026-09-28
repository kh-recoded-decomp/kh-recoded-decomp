#include "nitro/types.h"

typedef struct UnknownState_02060764 {
    u32 unk_00;
    void *target;
} UnknownState_02060764;

extern UnknownState_02060764 g_unknownState_02060764;

void func_0202d60c(u32 value)
{
    if (g_unknownState_02060764.target != NULL) {
        *(u32 *)((u8 *)g_unknownState_02060764.target + 0x600) = value;
    }
}
