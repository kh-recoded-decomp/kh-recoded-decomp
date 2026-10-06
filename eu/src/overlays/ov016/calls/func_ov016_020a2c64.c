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
extern unsigned int AdvanceAnimationTracks();
extern unsigned int ActorRegistry_GetEntityByIndex();
extern unsigned int GetMaximumFieldValue();

void func_ov016_020a2c64(int work) {
  ActorNode *actor;
  int finished;
  unsigned int value;

  if ((*(u32 *)(work + 0xc0) & 0x20) != 0) {
    actor = ActorRegistry_GetEntityByIndex((u32)*(u8 *)(work + 0x32));
    finished = AdvanceAnimationTracks(&actor->flags_004,0x1000);
    if (finished != 0) {
      *(u32 *)(work + 0xc0) = *(u32 *)(work + 0xc0) & 0xffffffdf;
    }
    value = GetMaximumFieldValue(&actor->flags_004);
    *(unsigned int *)(work + 0xc4) = value;
  }
}
