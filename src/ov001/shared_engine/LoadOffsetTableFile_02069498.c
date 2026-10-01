#include "nitro/types.h"

typedef struct {
    u8 count;
    u8 pad_01[3];
    u32 offsets[1];
} OffsetTableFile;

typedef struct {
    OffsetTableFile *file;
} OffsetTableHolder;

extern OffsetTableHolder *data_ov001_020a047c;
extern char data_ov001_0209eae0[];
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern u8 *func_ov001_020636e4(void);
extern u32 findSharedResourceByName_0202cd8c(u8 *table, char *name);
extern OffsetTableFile *func_0202c478(u32 fileId, u32 flags);

void LoadOffsetTableFile_02069498(void)
{
    OffsetTableHolder *holder = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(OffsetTableHolder));
    int i = 0;
    u8 *base;
    u32 index;
    OffsetTableFile *file;

    func_01ff8740(0, holder, sizeof(OffsetTableHolder));
    base = func_ov001_020636e4();
    index = findSharedResourceByName_0202cd8c(func_ov001_020636e4(), data_ov001_0209eae0);
    file = func_0202c478((0x80000000 | (((u32)base + 0x8000) & 0xfffffc) << 7) | (index & 0x1ff), 2);
    holder->file = file;
    for (; i < file->count; i++) {
        file->offsets[i] = (u32)((u8 *)file + file->offsets[i]);
    }
    data_ov001_020a047c = holder;
}
