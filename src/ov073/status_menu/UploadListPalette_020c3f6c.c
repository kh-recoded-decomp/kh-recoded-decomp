#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x10];
    u16 palette[0x30];
} ListView;

extern void DC_FlushRange_0200344c(const void *addr, u32 size);
extern void func_020072b4(const void *source, u32 offset, u32 size);
extern int GFXi_EnqueueCommand_02014090(int type, int destOffset, void *source, int size);

void UploadListPalette_020c3f6c(ListView *list, BOOL immediate)
{
    if (immediate) {
        DC_FlushRange_0200344c(list->palette, sizeof(list->palette));
        func_020072b4(list->palette, 0xa0, sizeof(list->palette));
        return;
    }
    GFXi_EnqueueCommand_02014090(0x1f, 0xa0, list->palette, sizeof(list->palette));
}
