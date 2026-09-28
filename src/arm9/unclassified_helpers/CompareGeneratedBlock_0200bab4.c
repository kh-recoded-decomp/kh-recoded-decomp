#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    void *unk_14;
    u32 unk_18;
} SyncGlobal;

extern SyncGlobal g_syncGlobal_02057b00;

extern void func_01ff8830(void *dst, int value, int size);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern int SetModeAndCallback_0200d694(int mode);
extern void func_0200d9f4(void *compareBuffer, void *param2, void *param3, void *buffer, u32 size);

BOOL CompareGeneratedBlock_0200bab4(int *expected, void *param2, void *param3, int useCallback) {
    int compareBuffer[5];
    u8 buffer[64];
    int savedMode;
    u32 offset;

    func_01ff8830(compareBuffer, 0, 0x14);
    MI_CpuCopy8_01ff89a8(g_syncGlobal_02057b00.unk_14, buffer, g_syncGlobal_02057b00.unk_18);
    savedMode = 0;
    if (useCallback != 0) {
        savedMode = SetModeAndCallback_0200d694(1);
    }
    func_0200d9f4(compareBuffer, param2, param3, buffer, g_syncGlobal_02057b00.unk_18);
    if (useCallback != 0) {
        SetModeAndCallback_0200d694(savedMode);
    }
    offset = 0;
    do {
        if (*(int *)((u8 *)compareBuffer + offset) != *(int *)((u8 *)expected + offset)) break;
        offset += 4;
    } while (offset < 0x14);
    return offset == 0x14;
}
