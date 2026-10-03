#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LinkSnapshot {
    s32 height;
    s32 baseHeight;
    u16 flags;
    u8 state;
    u8 pad_0b;
} LinkSnapshot;

typedef struct LinkOwner {
    u8 pad_00[0x59];
    u8 listId;
    u8 pad_5a[6];
    LinkSnapshot *snapshots;
} LinkOwner;

typedef struct LinkObject {
    u32 status;
    LinkOwner *owner;
    void *work;
    void (*update)(void);
    u8 shape[0x20];
    u16 renderFlags;
    u8 tag;
    u8 slotIndex;
    fx32 fallSpeed;
    VecFx32 position;
    u16 linkId;
    u8 linkSlot;
    s8 animIndex;
    u8 pad_48[4];
    s8 sizeX;
    s8 sizeY;
    u8 phase;
    u8 state : 3;
    u8 stateMid : 3;
    u8 isLead : 1;
    u8 stateHigh : 1;
    u8 counter;
    u8 linkIndex;
    u8 kind;
    s8 callbackId;
    u8 pad_54[2];
    s16 frame;
    u8 pad_58[2];
    u16 flags;
    s16 rotX;
    s16 rotY;
    s16 rotZ;
    u8 pad_62[2];
    s32 baseHeight;
} LinkObject;

extern LinkObject *func_ov001_02086308(void *owner, int kind);
extern void BuildCollisionShape_02080834(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY,
                                         fx32 sizeZ, s32 angle, BOOL allocate, int mode);
extern void AppendNodeToActiveList_02086fac(u8 listId, int kind, u8 tag);
extern int GetEntryUnlockState_02087478(BOOL skipModeCheck, int flagOffset, u32 entryId, u32 slot);
extern BOOL IsDestroyed_020a31f8(LinkObject *self);
extern void func_ov019_020a2ecc(void);

u8 SpawnLinkedObject_020a3328(void *owner, int kind, u8 tag, u16 linkId, u8 linkSlot, const VecFx32 *position,
                              s8 sizeX, s8 sizeY, s16 rotX, s16 rotY, s16 rotZ, s8 unused, s8 linkIndex,
                              u32 options)
{
    LinkObject *entry = func_ov001_02086308(owner, kind);
    int mode = 2;
    LinkOwner *parent = entry->owner;
    LinkSnapshot *snapshots;

    entry->position = *position;
    entry->animIndex = 0;
    entry->fallSpeed = -0x1000;
    entry->state = 0;
    entry->flags = 0;
    entry->sizeX = sizeX;
    entry->sizeY = sizeY;
    entry->rotX = rotX;
    entry->rotY = rotY;
    entry->rotZ = rotZ;
    entry->baseHeight = entry->position.y;
    entry->linkIndex = linkIndex < 0 ? 0xff : linkIndex;
    entry->callbackId = -1;
    entry->counter = 0;
    entry->kind = 0x15;
    entry->isLead = 0;
    entry->phase = 1;
    entry->frame = 0;
    entry->linkId = linkId;
    entry->linkSlot = linkSlot;
    if (entry->linkIndex != 0xff) {
        entry->flags |= 0x100;
    }
    entry->renderFlags |= 8;
    if (options & 1) {
        mode = 1;
    } else if (options & 2) {
        mode = 0;
        entry->sizeY--;
    }
    if (!(options & 0x10)) {
        entry->flags |= 0x800;
    }
    snapshots = parent->snapshots;
    if (snapshots != NULL) {
        int index = entry->slotIndex;
        LinkSnapshot *snapshot = &snapshots[index];
        entry->flags = snapshot->flags;
        entry->state = snapshot->state;
        entry->position.y = snapshots[index].height;
        entry->baseHeight = snapshot->baseHeight;
    }
    switch (GetEntryUnlockState_02087478(mode, entry->sizeY, entry->linkId, entry->linkSlot)) {
    case 0:
        entry->flags |= 0x400;
        entry->phase = 3;
        break;
    case 1:
        entry->flags |= 0x200;
        break;
    case 2:
        entry->flags &= ~0x600;
        break;
    }
    if (IsDestroyed_020a31f8(entry)) {
        entry->update = NULL;
        entry->state = 2;
        entry->phase = 0;
    } else {
        entry->update = func_ov019_020a2ecc;
        BuildCollisionShape_02080834(entry->shape, &entry->position, 3, 0x1800, 0x1800, 0x1800, 0, 1, 4);
        entry->renderFlags |= 0x10;
    }
    entry->tag = tag;
    AppendNodeToActiveList_02086fac(parent->listId, kind, entry->tag);
    return entry->tag;
}
