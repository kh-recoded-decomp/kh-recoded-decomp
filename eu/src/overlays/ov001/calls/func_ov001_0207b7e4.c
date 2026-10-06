#include "nitro/types.h"

extern u32 sOv001_UiBtlFormatSLanguageP2_0209eff4;
extern void OS_SNPrintf(void *buffer, u32 size, const char *format, ...);
extern u32 Msg_OpenContainerAndReadHeader(void *buffer, u32 arg1, u32 arg2);

void func_ov001_0207b7e4(u32 *out, u32 value, u32 unused, u32 pad)
{
    char buffer[32];
    u32 padStack;

    padStack = pad;
    OS_SNPrintf(buffer, 0x20, (const char *)&sOv001_UiBtlFormatSLanguageP2_0209eff4, value);
    *out = Msg_OpenContainerAndReadHeader(buffer, 0xe, 0);
}
