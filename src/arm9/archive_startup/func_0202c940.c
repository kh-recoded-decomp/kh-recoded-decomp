#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 refCount;
    u16 loadCount;
    u8 pad_06[6];
    void *resource;
    void *cachedBlock;
} ResourceSlot;

extern u32 g_reentryGuard_02056014;
extern void *FindTextureResourceBlock_0201ac70(const void *header);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern int CallSelectionHandler_0202d328(void *a, void *b);
extern s32 func_0202d098(void *resource, void *heap);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);

void *func_0202c940(ResourceSlot *info, void *textureHeader, int flag)
{
    void *block = NULL;
    u32 savedGuard = g_reentryGuard_02056014;
    BOOL foundFresh = FALSE;

    g_reentryGuard_02056014 = flag;

    if (info->refCount == 0) {
        void *cached = info->cachedBlock;
        if (cached != NULL) {
            block = cached;
        } else if (textureHeader != NULL) {
            block = FindTextureResourceBlock_0201ac70(textureHeader);
            foundFresh = TRUE;
        }
        if (*(u32 *)info->resource == 0x4850414b) {
            CallSelectionHandler_0202d328(info->resource, block);
        } else {
            func_0202d098(info->resource, block);
        }
        if (foundFresh) {
            u32 size = *(u32 *)((u8 *)block + 0x14);
            void *allocated = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, 0x20);
            info->cachedBlock = allocated;
            MI_CpuCopy8_01ff89a8(block, allocated, size);
        }
    }

    info->refCount++;
    g_reentryGuard_02056014 = savedGuard;
    if (flag != 0) {
        info->loadCount++;
    }
    return info->resource;
}
