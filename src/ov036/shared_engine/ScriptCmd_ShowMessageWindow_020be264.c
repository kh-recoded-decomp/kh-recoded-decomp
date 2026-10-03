#include "nitro/types.h"

typedef struct ScriptVm {
    u8 pad_000[0x628];
    s32 skipWait;
} ScriptVm;

extern int func_02025dac(ScriptVm *vm, unsigned short *operand);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern void Utf8ToUcs2_020512b4(const char *src, u16 *dst, int dstCount);
extern BOOL OpenMessageTextWindow_020c2fc8(const u16 *text);

BOOL ScriptCmd_ShowMessageWindow_020be264(ScriptVm *vm, unsigned short *operand)
{
    u16 text[0x100];
    const char *message = (const char *)func_02025dac(vm, operand);
    u32 mode;

    if (vm->skipWait != 0) {
        return TRUE;
    }
    mode = ReadSessionPackedBits_02064574(0x1a00, 2);
    if (mode == 1 || mode == 3) {
        return TRUE;
    }
    Utf8ToUcs2_020512b4(message, text, 0x100);
    OpenMessageTextWindow_020c2fc8(text);
    return TRUE;
}
