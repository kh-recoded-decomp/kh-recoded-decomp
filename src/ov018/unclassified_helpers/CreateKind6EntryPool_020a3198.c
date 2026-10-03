#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind6EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    fx32 range;
    int active;
    VecFx32 extent;
    u8 mode;
    u8 pad_59;
    u8 kind;
    u8 pad_5b[0x79];
    int unk_d4;
    u8 pad_d8[0x100];
    int unk_1d8;
} Kind6EntryPool;

extern Kind6EntryPool *CreateEntryPool_02086258(int headerSize, int entrySize, int count);
extern void func_ov018_020a1ef8(void);
extern void func_ov018_020a3194(void);
extern void func_ov018_020a2214(void);
extern void func_ov018_020a2240(void);
extern void func_ov018_020a229c(void);
extern void GetActorVelocity_020a2640(void);
extern void func_ov018_020a2400(void);
extern void GetRaisedTargetPosition_020a2600(void);
extern void func_ov018_020a3190(void);
extern void func_ov018_020a2200(void);
extern void func_ov018_020a267c(void);

Kind6EntryPool *CreateKind6EntryPool_020a3198(int count)
{
    Kind6EntryPool *pool = CreateEntryPool_02086258(0x474, 0xbc, count);

    pool->active = 0;
    pool->mode = 3;
    pool->extent.x = 0x1800;
    pool->extent.y = 0x1800;
    pool->extent.z = 0x1800;
    pool->range = 0x3000;
    pool->callbacks[0] = func_ov018_020a1ef8;
    pool->callbacks[1] = func_ov018_020a3194;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = func_ov018_020a2214;
    pool->callbacks[5] = func_ov018_020a2240;
    pool->callbacks[6] = NULL;
    pool->callbacks[7] = func_ov018_020a229c;
    pool->callbacks[8] = GetActorVelocity_020a2640;
    pool->callbacks[9] = func_ov018_020a2400;
    pool->callbacks[10] = GetRaisedTargetPosition_020a2600;
    pool->callbacks[3] = func_ov018_020a3190;
    pool->callbacks[12] = func_ov018_020a2200;
    pool->callbacks[14] = func_ov018_020a267c;
    pool->kind = 6;
    pool->unk_d4 = 0;
    pool->unk_1d8 = 0;
    return pool;
}
