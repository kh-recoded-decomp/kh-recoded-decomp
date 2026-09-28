#include "nitro/types.h"

typedef struct PzOwner {
    u8 pad_000[0x210];
    void *pzResource;
} PzOwner;

extern u8 *func_ov001_020636e4(void);
extern int findSharedResourceByName_0202cd8c(u8 *table, const char *name);
extern void *func_0202c478(u32 fileId, u32 heapId);
extern char data_ov001_0209e9f0[];

void LoadPzResource_020663a4(PzOwner *owner)
{
    u8 *archive;
    int entryIndex;

    archive = func_ov001_020636e4();
    entryIndex = findSharedResourceByName_0202cd8c(func_ov001_020636e4(), data_ov001_0209e9f0);
    owner->pzResource =
        func_0202c478(((((u32)(archive + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (entryIndex & 0x1ff), 5);
}
