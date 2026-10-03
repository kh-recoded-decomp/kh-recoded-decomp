#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind5EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    fx32 range;
    int active;
    VecFx32 extent;
    u8 mode;
    u8 pad_59;
    u8 kind;
    u8 pad_5b[5];
    int owner;
    s16 groupId;
    u8 pad_66[2];
    void *resource;
} Kind5EntryPool;

extern Kind5EntryPool *CreateEntryPool_02086258(int headerSize, int entrySize, int count);
extern void HandleLinkEvent_020a2418(void);
extern void RefreshLeadLinkState_020a31a0(void);
extern void ReleaseOwnerResources_020a272c(void);
extern void GetObjectPositionIfValid_020a320c(void);
extern void HandleLinkHit_020a2774(void);
extern void TryGetExtraDataHandle_020a2c28(void);
extern void TryCollideWithCollider_020a2a08(void);
extern void GetRaisedFocusPoint_020a2bcc(void);
extern void ApplyDerivedIdState_020a3188(void);
extern void IsDestroyed_020a31f8(void);
extern void SnapshotLinkStates_020a3234(void);
extern void DrawActorModel_020a2c4c(void);

Kind5EntryPool *CreateKind5EntryPool_020a3284(int count, int unused, int owner)
{
    Kind5EntryPool *pool = CreateEntryPool_02086258(0x6c, 0x78, count);

    pool->active = 0;
    pool->mode = 3;
    pool->extent.x = 0x1800;
    pool->extent.y = 0x1800;
    pool->extent.z = 0x1800;
    pool->range = 0x3000;
    pool->callbacks[0] = HandleLinkEvent_020a2418;
    pool->callbacks[1] = RefreshLeadLinkState_020a31a0;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = ReleaseOwnerResources_020a272c;
    pool->callbacks[5] = NULL;
    pool->callbacks[6] = NULL;
    pool->callbacks[11] = GetObjectPositionIfValid_020a320c;
    pool->callbacks[7] = HandleLinkHit_020a2774;
    pool->callbacks[8] = TryGetExtraDataHandle_020a2c28;
    pool->callbacks[9] = TryCollideWithCollider_020a2a08;
    pool->callbacks[10] = GetRaisedFocusPoint_020a2bcc;
    pool->callbacks[3] = ApplyDerivedIdState_020a3188;
    pool->callbacks[12] = IsDestroyed_020a31f8;
    pool->callbacks[13] = SnapshotLinkStates_020a3234;
    pool->callbacks[14] = DrawActorModel_020a2c4c;
    pool->kind = 5;
    pool->owner = owner;
    pool->groupId = -1;
    pool->resource = NULL;
    return pool;
}
