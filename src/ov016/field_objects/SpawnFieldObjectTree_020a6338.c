#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpawnAttr {
    u32 flagA : 1;
    u32 flagB : 1;
    u32 low : 10;
    u32 high : 10;
    u32 group : 10;
} SpawnAttr;

typedef struct SpawnFlagRef {
    u32 index : 10;
    u32 sub : 12;
    u32 rest : 10;
} SpawnFlagRef;

typedef struct SpawnDesc {
    s32 kind;
    s32 tag;
    u16 entryId;
    u8 slot;
    u8 pad_0b;
    s32 mode;
    s32 phase;
    s32 param14;
    VecFx32 position;
    s32 param24;
    s16 prevId;
    s16 nextId;
    u8 pad_2c[4];
    s32 extraByte;
    u8 gridX;
    u8 gridY;
    u8 gridZ;
    u8 layer;
    SpawnAttr attr;
    u32 flagC : 1;
    u32 pad_3c : 31;
    s32 paramB8;
    s32 paramB4;
    s32 paramB0;
    SpawnFlagRef flagRef;
    s32 paramD0;
    s32 paramD4;
    s32 paramD8;
} SpawnDesc;

typedef struct Spawner {
    u8 pad_00[0x59];
    u8 listId;
    u8 pad_5a[0xc4 - 0x5a];
    s32 deferred;
} Spawner;

typedef struct FieldObject {
    u8 pad_00[4];
    Spawner *spawner;
    u8 pad_08[4];
    void *update;
    u8 pad_10[0x32 - 0x10];
    u8 result;
    u8 pad_33;
    s32 param34;
    VecFx32 position;
    u8 pad_44[3];
    u8 flag47;
    u8 pad_48[0x6c - 0x48];
    u16 entryId;
    u16 slot;
    u16 active : 1;
    u16 moved : 1;
    u16 flagA : 1;
    u16 flagB : 1;
    u16 chained : 1;
    u16 pad_70_5 : 2;
    u16 layer : 2;
    u16 pad_70_9 : 4;
    u16 flagC : 1;
    u16 locked : 1;
    u16 pad_70_15 : 1;
    s16 param72;
    u8 attrHigh;
    u8 attrLow;
    u8 pad_76;
    u8 mode;
    u8 pad_78[0x90 - 0x78];
    s16 prevId;
    s16 nextId;
    u32 flagIndex : 10;
    u32 flagSub : 12;
    u32 group : 10;
    s32 field98;
    s32 field9c;
    VecFx32 home;
    s32 paramAC;
    s32 paramB0;
    s32 paramB4;
    s32 paramB8;
    u8 gridX : 4;
    u8 gridY : 4;
    u8 gridZ : 4;
    u8 phase : 4;
    u8 lowBE : 4;
    u8 highBE : 4;
    u8 pad_bf;
    s32 fieldC0;
    u8 pad_c4[0xd0 - 0xc4];
    s32 paramD0;
    s32 paramD4;
    u32 paramD8;
    u8 pad_dc[0xe8 - 0xdc];
    s16 linkA;
    s16 linkB;
    u8 *extra;
} FieldObject;

extern FieldObject *func_ov001_02086308(void *pool, s32 kind);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void SetFieldObjectWeightByKind_020a29cc(FieldObject *obj, int kind);
extern int GetEntryUnlockState_02087478(BOOL skipModeCheck, u32 flagOffset, u32 entryId, u32 slot);
extern void ApplyFieldObjectSpawnEntry_020a5f18(FieldObject *obj);
extern void SpawnGroupMemberGrid_020bf468(FieldObject *obj, const SpawnDesc *desc);
extern void func_ov016_020a596c(void);
extern void func_ov016_020a2598(FieldObject *obj, u32 param);
extern void UpdateFieldObjectHighlight_020a227c(FieldObject *obj, BOOL visible);
extern void AppendNodeToActiveList_02086fac(u32 listId, u32 kind, u32 tag);

u8 SpawnFieldObjectTree_020a6338(void *pool, const SpawnDesc *desc)
{
    FieldObject *obj;
    Spawner *spawner;
    SpawnDesc child;
    u8 mode;
    int prevKind;
    int nextKind;
    int kind;
    int tag;
    int level;
    int x;
    int y;

    obj = func_ov001_02086308(pool, desc->kind);
    spawner = obj->spawner;
    if (desc->phase >= 5) {
        obj->extra = NNSi_FndAllocFromDefaultHeapEx_0202a19c(100, 4);
    } else {
        obj->extra = NULL;
    }
    obj->position = desc->position;
    obj->home = desc->position;
    obj->flag47 = 0;
    obj->param34 = desc->param24;
    obj->highBE = 0;
    obj->fieldC0 = 1;
    obj->flagA = desc->attr.flagA;
    obj->flagB = desc->attr.flagB;
    obj->attrHigh = desc->attr.high;
    obj->attrLow = desc->attr.low;
    obj->group = desc->attr.group;
    obj->entryId = desc->entryId;
    obj->slot = desc->slot;
    obj->phase = desc->phase;
    obj->prevId = desc->prevId;
    obj->nextId = desc->nextId;
    obj->paramB8 = desc->paramB8;
    obj->paramB4 = desc->paramB4;
    mode = desc->mode;
    obj->mode = mode;
    obj->paramB0 = desc->paramB0;
    obj->paramAC = obj->paramB0;
    obj->param72 = desc->param14;
    obj->layer = desc->layer;
    obj->gridX = desc->gridX;
    obj->gridY = desc->gridY;
    obj->gridZ = desc->gridZ;
    obj->flagC = desc->flagC;
    obj->flagIndex = desc->flagRef.index;
    obj->flagSub = desc->flagRef.sub;
    obj->mode = mode;
    obj->locked = 0;
    SetFieldObjectWeightByKind_020a29cc(obj, obj->mode);
    obj->active = 0;
    switch (obj->mode) {
    case 5:
        obj->paramD0 = desc->paramD0;
        obj->paramD8 = desc->paramD8;
        obj->paramD4 = desc->paramD4;
        break;
    case 11:
        obj->linkB = 0;
        obj->paramD8 = (obj->paramD8 & ~0xff) | 0xff;
        break;
    case 7:
        obj->paramD8 = 0;
        break;
    case 10:
        obj->active = 1;
        if (obj->entryId != 0xffff &&
            GetEntryUnlockState_02087478(FALSE, obj->flagIndex - 1, obj->entryId, obj->slot) != 0) {
            obj->mode = 1;
            SetFieldObjectWeightByKind_020a29cc(obj, 1);
        }
        break;
    case 14:
    case 15:
        if (obj->entryId != 0xffff &&
            GetEntryUnlockState_02087478(FALSE, obj->flagIndex - 1, obj->entryId, obj->slot) != 0) {
            obj->mode = (obj->mode == 14) ? 12 : 13;
        }
        obj->active = 1;
    case 9:
    case 12:
    case 13:
        obj->linkA = -1;
        obj->linkB = -1;
        obj->phase = 0;
        break;
    }
    obj->field98 = 0;
    obj->field9c = 0;
    obj->moved = 0;
    if (spawner->deferred != 0) {
        ApplyFieldObjectSpawnEntry_020a5f18(obj);
    }
    if (obj->phase >= 5) {
        if (spawner->deferred == 0) {
            obj->extra[2] = desc->extraByte;
        }
        SpawnGroupMemberGrid_020bf468(obj, desc);
        if (spawner->deferred != 0) {
            ApplyFieldObjectSpawnEntry_020a5f18(obj);
        }
    }
    obj->update = func_ov016_020a596c;
    func_ov016_020a2598(obj, 1);
    UpdateFieldObjectHighlight_020a227c(obj, TRUE);
    AppendNodeToActiveList_02086fac(spawner->listId, desc->kind, desc->tag);
    if (obj->phase < 5) {
        /* Spawn stacked or grid children */
        child = *desc;
        if (desc->gridY > 1) {
            tag = desc->tag + 1;
            prevKind = desc->kind;
            kind = prevKind + 1;
            obj->chained = 1;
            if (obj->mode == 2) {
                obj->locked = 1;
            } else {
                for (level = 1; level < obj->gridY; level++) {
                    child.position.y = desc->position.y + level * 0x1800;
                    if (level + 1 < obj->gridY) {
                        nextKind = kind + 1;
                    } else {
                        nextKind = -1;
                    }
                    child.kind = kind;
                    child.tag = tag;
                    child.prevId = prevKind;
                    child.nextId = nextKind;
                    child.gridX = 1;
                    child.gridY = 1;
                    child.gridZ = 1;
                    SpawnFieldObjectTree_020a6338(pool, &child);
                    prevKind = kind;
                    kind++;
                    tag++;
                }
            }
        } else {
            tag = desc->tag + 1;
            kind = desc->kind + 1;
            obj->chained = 0;
            for (y = 0; y < obj->gridZ; y++) {
                for (x = 0; x < obj->gridX; x++) {
                    if (x != 0 || y != 0) {
                        child.kind = kind;
                        child.tag = tag;
                        child.prevId = -1;
                        child.nextId = -1;
                        child.gridX = 1;
                        child.gridY = 1;
                        child.gridZ = 1;
                        child.position.x = desc->position.x + x * 0x1800;
                        child.position.z = desc->position.z + y * 0x1800;
                        SpawnFieldObjectTree_020a6338(pool, &child);
                        kind++;
                        tag++;
                    }
                }
            }
        }
    }
    return obj->result;
}
