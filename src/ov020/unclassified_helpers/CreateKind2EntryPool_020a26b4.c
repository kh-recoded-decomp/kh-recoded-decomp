#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind2EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    s32 selected;
    int active;
    u8 pad_4c[0xe];
    u8 kind;
} Kind2EntryPool;

extern Kind2EntryPool *CreateEntryPool_02086258(int headerSize, int entrySize, int count);
extern void func_ov020_020a2090(void);
extern void func_ov020_020a21b4(void);
extern void func_ov020_020a2348(void);
extern void func_ov020_020a21b8(void);
extern void func_ov020_020a21c0(void);
extern void func_ov020_020a2344(void);
extern void func_ov020_020a252c(void);
extern void func_ov020_020a25a0(void);

Kind2EntryPool *CreateKind2EntryPool_020a26b4(int count)
{
    Kind2EntryPool *pool = CreateEntryPool_02086258(0x60, 0x50, count);

    pool->active = 0;
    pool->selected = -1;
    pool->callbacks[0] = func_ov020_020a2090;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = NULL;
    pool->callbacks[5] = NULL;
    pool->callbacks[6] = func_ov020_020a21b4;
    pool->callbacks[14] = func_ov020_020a2348;
    pool->callbacks[7] = func_ov020_020a21b8;
    pool->callbacks[8] = NULL;
    pool->callbacks[9] = func_ov020_020a21c0;
    pool->callbacks[10] = NULL;
    pool->callbacks[3] = func_ov020_020a2344;
    pool->callbacks[1] = func_ov020_020a252c;
    pool->callbacks[11] = func_ov020_020a25a0;
    pool->kind = 2;
    return pool;
}
