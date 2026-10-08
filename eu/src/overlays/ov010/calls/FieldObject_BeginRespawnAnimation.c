#include "nitro/types.h"

typedef unsigned char LayoutU8;
typedef unsigned short LayoutU16;
typedef unsigned int LayoutU32;
typedef signed int LayoutFX32;

typedef struct VecFx32 {
    LayoutFX32 x;
    LayoutFX32 y;
    LayoutFX32 z;
} VecFx32;

typedef struct ModelResource {
    LayoutU8 unknown_000[0x08];
    LayoutU32 materialsRelativeOffset;
    LayoutU8 unknown_00c[0x0c];
    LayoutU8 materialCount;
} ModelResource;

typedef struct ActorNode {
    LayoutU32 flags_000;
    LayoutU16 flags_004;
    LayoutU8 unknown_006[0x76];
    ModelResource *modelResource;
    LayoutU16 halfword_080;
    LayoutU8 unknown_082[0x32];
    VecFx32 offset;
} ActorNode;

typedef struct ActorStorage {
    LayoutU8 unknownHeader[0x10];
    ActorNode actor;
} ActorStorage;

typedef struct ActorRegistry {
    LayoutU8 unknownHeader[0x20];
    ActorStorage *actors[1];
} ActorRegistry;

extern unsigned int func_01ffb2f8();
extern unsigned int Anim_GetFrame();
extern unsigned int Flags16_ClearBit1();
extern unsigned int ActorSlot_SetFlag8ByIndex();
extern unsigned int ActorRegistry_GetEntityByIndex();
extern unsigned int func_ov001_02063a4c();
extern unsigned int GetClampedTimerValue();
extern unsigned int GetActiveSceneSlot();
extern unsigned int RebindAnimTracks();
extern unsigned int selectJointAnimationBlend();
extern void FieldObject_AdvanceRespawnAnimation(void);

unsigned int FieldObject_BeginRespawnAnimation(int work)
{
    int indexOrMode;
    u32 timer;
    ActorNode *actor;
    int node;
    unsigned int animation;

    indexOrMode = func_ov001_02063a4c();
    if ((indexOrMode == 4) &&
        (timer = GetClampedTimerValue(), timer <= 30000)) {
        indexOrMode = 1;
        ActorSlot_SetFlag8ByIndex(*(u8 *)(work + 0x38), 1);
        actor = ActorRegistry_GetEntityByIndex((u32)*(u8 *)(work + 0x38));
        RebindAnimTracks(&actor->flags_004, 0, 0);
        Flags16_ClearBit1(&actor->flags_004);
        do {
            node = GetActiveSceneSlot(indexOrMode);
            animation = Anim_GetFrame(node, 0);
            selectJointAnimationBlend(node, 0, node + 0xd8, 1);
            selectJointAnimationBlend(node, 2, node + 0xd8, 1);
            func_01ffb2f8(node, 0, animation);
            func_01ffb2f8(node, 2, animation);
            indexOrMode = indexOrMode + 1;
        } while (indexOrMode <= 2);
        *(unsigned int *)(work + 0x58) = 1;
        return (u32)FieldObject_AdvanceRespawnAnimation;
    }
    return 0;
}
