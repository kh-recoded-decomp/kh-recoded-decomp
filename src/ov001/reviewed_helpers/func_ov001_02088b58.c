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
extern unsigned int func_02036588();
extern unsigned int func_02036810();
extern unsigned int func_arm9_02036240();
extern unsigned int func_ov001_0208a3e0();
extern unsigned int func_ov001_0208a458();

void func_ov001_02088b58(int *owner) {
  u32 flags;
  ActorNode *actor;
  int work;

  func_ov001_0208a3e0(owner);
  func_ov001_0208a458(owner);
  work = *owner;
  if (work != 0) {
    *(int *)(work + 0xf04) = *(int *)(work + 0xf04) + -1;
    if (((*(int *)(*owner + 0xf04) == 0) &&
        (work = func_02036810(*(u32 *)(*owner + 0xf00) & 0xffff), work != 0)) &&
       (flags = func_02036588(*(u32 *)(*owner + 0xf00) & 0xffff), (flags & 4) != 0)) {
      actor = func_arm9_02036240(*(u32 *)(*owner + 0xf00) & 0xffff);
      actor->flags_004 = actor->flags_004 & 0xffe7;
    }
    *owner = 0;
  }
}
