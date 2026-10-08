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

extern unsigned int RebindAnimTracks();
extern unsigned int ActorRegistry_GetEntityByIndex();
extern unsigned int func_ov001_02063a4c();
extern unsigned int GetClampedTimerValue();
extern void FieldObject_RespawnAnimationComplete(void);

unsigned int FieldObject_AdvanceRespawnAnimation(int work)
{
    int mode;
    u32 timer;
    ActorNode *actor;

    mode = func_ov001_02063a4c();
    if ((mode == 4) && (timer = GetClampedTimerValue(), timer <= 10000)) {
        actor = ActorRegistry_GetEntityByIndex((u32)*(u8 *)(work + 0x38));
        RebindAnimTracks(&actor->flags_004, 1, 0);
        *(unsigned int *)(work + 0x58) = 2;
        return (u32)FieldObject_RespawnAnimationComplete;
    }
    return 0;
}
