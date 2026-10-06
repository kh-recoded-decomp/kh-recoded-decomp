#include "nitro/types.h"

typedef struct {
    u8 data[0x10];
} EntryBuffer;

typedef struct {
    u8 pad_00[0x38];
    EntryBuffer buffers[3];
    u32 results[4];
} EntryCache;

typedef struct {
    u8 pad_0000[0x2740];
    EntryCache cache;
} Session;

extern Session *data_ov001_020a0480;
extern u32 func_ov001_0206dc38(void);
extern u32 GetBoundedEntryField(int index);
extern u32 CopyActiveBlockIfPresent(u32 entry, EntryBuffer *buffer);

void func_ov001_02064d88(void)
{
    EntryCache *cache = &data_ov001_020a0480->cache;
    int index = 0;

    if ((int)func_ov001_0206dc38() > 0)
    {
        do
        {
            cache->results[index] = CopyActiveBlockIfPresent(GetBoundedEntryField(index), &cache->buffers[index]);
            index++;
        } while (index < (int)func_ov001_0206dc38());
    }
}
