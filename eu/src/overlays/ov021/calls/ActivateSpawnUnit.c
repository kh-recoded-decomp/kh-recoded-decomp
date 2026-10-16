#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct SpawnOwner SpawnOwner;
struct SpawnOwner {
    u8 unknown00[0x94];
    u16 yaw;
    u8 unknown96[0xbc - 0x96];
    VecFx32 position;
    u8 unknownc8[0x1f0 - 0xc8];
    int (*handler)(SpawnOwner *owner, int index, int argument, int mode);
};

typedef struct SpawnUnit {
    u8 unknown00[0x3c];
    s8 entryIndex;
    u8 unknown3d[3];
    s8 flags;
    u8 unknown41[3];
    u16 animationFlags;
    u8 unknown46[0xc0 - 0x46];
    u16 yaw;
    u8 unknownc2[0xe8 - 0xc2];
    VecFx32 position;
    VecFx32 scale;
    u8 unknown100[0x150 - 0x100];
    u8 animationTable[0x34];
    fx32 baseScale;
    s16 callbackIndex;
} SpawnUnit;

typedef struct SpawnPlacement {
    SpawnOwner *owner;
    VecFx32 position;
} SpawnPlacement;

typedef char SpawnOwnerYawOffset[(u32)&((SpawnOwner *)0)->yaw == 0x94 ? 1 : -1];
typedef char SpawnOwnerPositionOffset[(u32)&((SpawnOwner *)0)->position == 0xbc ? 1 : -1];
typedef char SpawnOwnerHandlerOffset[(u32)&((SpawnOwner *)0)->handler == 0x1f0 ? 1 : -1];
typedef char SpawnUnitEntryOffset[(u32)&((SpawnUnit *)0)->entryIndex == 0x3c ? 1 : -1];
typedef char SpawnUnitFlagsOffset[(u32)&((SpawnUnit *)0)->flags == 0x40 ? 1 : -1];
typedef char SpawnUnitAnimationOffset[(u32)&((SpawnUnit *)0)->animationFlags == 0x44 ? 1 : -1];
typedef char SpawnUnitYawOffset[(u32)&((SpawnUnit *)0)->yaw == 0xc0 ? 1 : -1];
typedef char SpawnUnitPositionOffset[(u32)&((SpawnUnit *)0)->position == 0xe8 ? 1 : -1];
typedef char SpawnUnitScaleOffset[(u32)&((SpawnUnit *)0)->scale == 0xf4 ? 1 : -1];
typedef char SpawnUnitTableOffset[(u32)&((SpawnUnit *)0)->animationTable == 0x150 ? 1 : -1];
typedef char SpawnUnitBaseScaleOffset[(u32)&((SpawnUnit *)0)->baseScale == 0x184 ? 1 : -1];
typedef char SpawnUnitCallbackOffset[(u32)&((SpawnUnit *)0)->callbackIndex == 0x188 ? 1 : -1];
typedef char SpawnPlacementPositionOffset[(u32)&((SpawnPlacement *)0)->position == 4 ? 1 : -1];
typedef char SpawnPlacementSize[sizeof(SpawnPlacement) == 16 ? 1 : -1];

extern const s16 gSinFx12Table[];
extern u32 GetBoundedEntryField(int index);
extern void GetSelectionSlotPosition(VecFx32 *out, u32 entryIndex, int slot);
extern void MTX_RotY33_(MtxFx33 *matrix, fx32 sinValue, fx32 cosValue);
extern void MTX_MultVec33(const VecFx32 *source, const MtxFx33 *matrix, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void RebindAnimTracks_020aef84(void *state, void *table, int index);

static inline void CallSpawnOwnerHandler(SpawnOwner *owner, int index,
                                         int argument, int mode)
{
    if (owner->handler != NULL) {
        owner->handler(owner, index, argument, mode);
    }
}

/* Place the spawn slot relative to its owner, reset its animation, and activate it. */
VecFx32 ActivateSpawnUnit(SpawnUnit *unit, int slot)
{
    MtxFx33 rotation;
    SpawnPlacement placement;
    placement.owner = (SpawnOwner *)GetBoundedEntryField(unit->entryIndex);
    u16 angle = placement.owner->yaw - 0x8000;
    u16 yaw = angle + 0x8000;
    int index;

    GetSelectionSlotPosition(&placement.position, unit->entryIndex, slot);
    index = yaw >> 4;
    MTX_RotY33_(&rotation, gSinFx12Table[index],
                gSinFx12Table[(0x400 - index) & 0xfff]);
    MTX_MultVec33(&placement.position, &rotation, &placement.position);
    VEC_Add(&placement.position, &placement.owner->position, &placement.position);
    if (!(unit->flags & 2)) {
        CallSpawnOwnerHandler(placement.owner, unit->callbackIndex, 0, 2);
    }
    RebindAnimTracks_020aef84(&unit->animationFlags, unit->animationTable, 0);
    unit->position = placement.position;
    unit->yaw = yaw;
    unit->animationFlags |= 0x20;
    unit->scale.z = unit->baseScale;
    unit->scale.y = unit->scale.z;
    unit->scale.x = unit->scale.y;
    unit->flags |= 1;
    return placement.position;
}
