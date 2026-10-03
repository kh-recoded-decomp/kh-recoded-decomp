#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind4EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    fx32 range;
    int active;
    VecFx32 extent;
    u8 mode;
    u8 pad_59;
    u8 kind;
    u8 pad_5B[0x89];
    void *messageHead;
    u8 pad_E8[0xdc];
    void *pool0;
    void *pool1;
    void *pool2;
    void *pool3;
    void *pool4;
    u8 pad_1D8[0x14];
    void *pendingList;
} Kind4EntryPool;

extern Kind4EntryPool *CreateEntryPool_02086258(int headerSize, int entrySize, int count);
extern void ResetPoolDefaultParams_020a4e50(Kind4EntryPool *pool);
extern void func_ov017_020a2bd0(void);
extern void func_ov017_020a3948(void);
extern void func_ov017_020a2e64(void);
extern void func_ov017_020a2ea0(void);
extern void func_ov017_020a2f08(void);
extern void func_ov017_020a3284(void);
extern void func_ov017_020a30e4(void);
extern void func_ov017_020a3240(void);
extern void func_ov017_020a3944(void);
extern void IsState1Or2_020a2e4c(void);
extern void func_ov017_020a32bc(void);

Kind4EntryPool *CreateKind4EntryPool_020a3a28(int count)
{
    Kind4EntryPool *pool = CreateEntryPool_02086258(0x1f0, 0x84, count);

    pool->active = 0;
    pool->mode = 3;
    pool->extent.x = 0x1800;
    pool->extent.y = 0x1800;
    pool->extent.z = 0x1800;
    pool->range = 0x3000;
    pool->callbacks[0] = func_ov017_020a2bd0;
    pool->callbacks[1] = func_ov017_020a3948;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = func_ov017_020a2e64;
    pool->callbacks[5] = func_ov017_020a2ea0;
    pool->callbacks[6] = NULL;
    pool->callbacks[7] = func_ov017_020a2f08;
    pool->callbacks[8] = func_ov017_020a3284;
    pool->callbacks[9] = func_ov017_020a30e4;
    pool->callbacks[10] = func_ov017_020a3240;
    pool->callbacks[3] = func_ov017_020a3944;
    pool->callbacks[12] = IsState1Or2_020a2e4c;
    pool->callbacks[14] = func_ov017_020a32bc;
    pool->kind = 4;
    ResetPoolDefaultParams_020a4e50(pool);
    pool->pool0 = NULL;
    pool->pool1 = NULL;
    pool->pool2 = NULL;
    pool->pool3 = NULL;
    pool->pool4 = NULL;
    pool->messageHead = NULL;
    pool->pendingList = NULL;
    return pool;
}
