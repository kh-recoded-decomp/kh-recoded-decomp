#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OrbitSlot {
    fx32 angle;
    fx32 radius;
} OrbitSlot;

typedef struct Actor {
    u8 pad_0000[0x1738];
    VecFx32 orbitCenter;
    OrbitSlot *orbitSlots;
    u8 pad_1748[0x1812 - 0x1748];
    s16 effectGroupId;
} Actor;

extern s32 func_ov021_020a8ca0(void *effectResource, s32 groupId);
extern OrbitSlot *func_ov059_020cac1c(OrbitSlot *slot, s32 slotIndex);
extern VecFx32 *Actor_GetModelPosition_020cd0d8(Actor *actor);
extern void func_0204d8d0(s32 soundId, s32 option);

void Actor_InitOrbitSlots_020cab6c(Actor *actor, s32 unused, void *effectResource)
{
    s32 i;

    for (i = 0; i < 7; i++) {
        func_ov021_020a8ca0(effectResource, actor->effectGroupId);
        func_ov059_020cac1c(&actor->orbitSlots[i], i);
    }
    actor->orbitCenter = *Actor_GetModelPosition_020cd0d8(actor);
    actor->orbitCenter.y = 0;
    func_0204d8d0(0xcc, 0);
}
