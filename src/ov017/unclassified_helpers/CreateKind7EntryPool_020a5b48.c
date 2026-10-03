#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind7EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    fx32 range;
    int active;
    VecFx32 extent;
    u8 mode;
    u8 pad_59;
    u8 kind;
} Kind7EntryPool;

extern Kind7EntryPool *CreateEntryPool_02086258(int headerSize, int entrySize, int count);
extern void func_ov017_020a5288(void);
extern void func_ov017_020a5a90(void);
extern void func_ov017_020a5438(void);
extern void func_ov017_020a5454(void);
extern void func_ov017_020a5734(void);
extern void func_ov017_020a55e8(void);
extern void func_ov017_020a56f4(void);
extern void func_ov017_020a5a78(void);
extern void func_ov017_020a50e4(void);
extern void func_ov017_020a574c(void);

Kind7EntryPool *CreateKind7EntryPool_020a5b48(int count)
{
    Kind7EntryPool *pool = CreateEntryPool_02086258(0x60, 0x70, count);

    pool->active = 0;
    pool->mode = 3;
    pool->extent.x = 0x1800;
    pool->extent.y = 0x1800;
    pool->extent.z = 0x1800;
    pool->range = 0x3000;
    pool->callbacks[0] = func_ov017_020a5288;
    pool->callbacks[1] = func_ov017_020a5a90;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = func_ov017_020a5438;
    pool->callbacks[5] = NULL;
    pool->callbacks[6] = NULL;
    pool->callbacks[7] = func_ov017_020a5454;
    pool->callbacks[8] = func_ov017_020a5734;
    pool->callbacks[9] = func_ov017_020a55e8;
    pool->callbacks[10] = func_ov017_020a56f4;
    pool->callbacks[3] = func_ov017_020a5a78;
    pool->callbacks[12] = func_ov017_020a50e4;
    pool->callbacks[14] = func_ov017_020a574c;
    pool->kind = 7;
    return pool;
}
