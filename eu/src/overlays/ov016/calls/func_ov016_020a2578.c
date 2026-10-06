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
extern unsigned int QuadTree_ReinsertNodeIfFlagSet();
extern unsigned int GetActorRegistry();
extern unsigned int ActorRegistry_GetEntityByIndex();

void func_ov016_020a2578(int work) {
  int registry;
  ActorNode *actor;

  registry = GetActorRegistry();
  actor = ActorRegistry_GetEntityByIndex((u32)*(u8 *)(work + 0x32));
  if (((registry != 0) && ((actor->flags_000 & 0x10) == 0)) && ((actor->flags_000 & 8) != 0)) {
    actor[1].unknown_006[0x52] = actor[1].unknown_006[0x52] | 1;
    QuadTree_ReinsertNodeIfFlagSet
              ((void *)**(unsigned int **)(registry + 4),(int)(actor[1].unknown_006 + 0x46));
  }
}
