#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind3EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    s32 selected;
    int active;
    u8 pad_4c[0xe];
    u8 kind;
} Kind3EntryPool;

extern Kind3EntryPool *CreateEntryPool_02086258(int headerSize, int entrySize, int count);
extern void func_ov020_020a349c(void);
extern void func_ov020_020a3578(void);
extern void DrawStackedPanels_020a3724(void);
extern void func_ov020_020a357c(void);
extern void func_ov020_020a3584(void);
extern void TryGetFieldHandle_020a3700(void);

Kind3EntryPool *CreateKind3EntryPool_020a3940(int count)
{
    Kind3EntryPool *pool = CreateEntryPool_02086258(0x60, 0x5c, count);

    pool->active = 0;
    pool->selected = -1;
    pool->callbacks[0] = func_ov020_020a349c;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = NULL;
    pool->callbacks[5] = NULL;
    pool->callbacks[6] = func_ov020_020a3578;
    pool->callbacks[14] = DrawStackedPanels_020a3724;
    pool->callbacks[7] = func_ov020_020a357c;
    pool->callbacks[9] = func_ov020_020a3584;
    pool->callbacks[8] = TryGetFieldHandle_020a3700;
    pool->callbacks[10] = NULL;
    pool->kind = 3;
    return pool;
}
