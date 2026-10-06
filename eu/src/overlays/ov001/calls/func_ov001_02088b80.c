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

typedef struct ScriptOperand {
    short type;
    LayoutU8 undecodedPayload[6];
} ScriptOperand;
extern unsigned int ActorSlot_GetFlagsByIndex();
extern unsigned int ActorSlot_GetByIndex();
extern unsigned int ActorRegistry_GetEntityByIndex();
extern unsigned int ClearActorTimerFields();
extern unsigned int func_ov001_0208a480();

void func_ov001_02088b80(int *owner) {
  u32 flags;
  ActorNode *actor;
  int work;

  ClearActorTimerFields(owner);
  func_ov001_0208a480(owner);
  work = *owner;
  if (work != 0) {
    *(int *)(work + 0xf04) = *(int *)(work + 0xf04) + -1;
    if (((*(int *)(*owner + 0xf04) == 0) &&
        (work = ActorSlot_GetByIndex(*(u32 *)(*owner + 0xf00) & 0xffff), work != 0)) &&
       (flags = ActorSlot_GetFlagsByIndex(*(u32 *)(*owner + 0xf00) & 0xffff), (flags & 4) != 0)) {
      actor = ActorRegistry_GetEntityByIndex(*(u32 *)(*owner + 0xf00) & 0xffff);
      actor->flags_004 = actor->flags_004 & 0xffe7;
    }
    *owner = 0;
  }
}
