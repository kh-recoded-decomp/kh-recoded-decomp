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
extern unsigned int data_ov001_020a0500;
extern unsigned int ActorChannel_SelectBuffer();
extern unsigned int LoadDefaultProjectionValues();
extern unsigned int func_01ffb12c();
extern unsigned int camera_commit_explicit_projection();
extern unsigned int ActorSlot_GetFlagsByIndex();
extern unsigned int ActorRegistry_GetEntityByIndex();
extern unsigned int DispatchModeUpdate();

void func_ov001_020887a4(void) {
  int work;
  u32 flags;
  ActorNode *actor;
  int index;
  int slot;
  u8 projection [56];

  work = data_ov001_020a0500;
  index = 0;
  do {
    if (*(int *)(data_ov001_020a0500 + index * 4 + 0x3f08) != -1) break;
    index = index + 1;
  } while (index < 5);
  if (index != 5) {
    LoadDefaultProjectionValues(projection);
    camera_commit_explicit_projection(projection,0x999a,-0x999a,-0xcccd,0xcccd);
    index = 0;
    do {
      slot = work + index * 4;
      if (*(u32 *)(slot + 0x3f08) != 0xffffffff) {
        flags = ActorSlot_GetFlagsByIndex(*(u32 *)(slot + 0x3f08) & 0xffff);
        if ((flags & 2) == 0) {
          *(unsigned int *)(slot + 0x3f08) = 0xffffffff;
        }
        else {
          actor = ActorRegistry_GetEntityByIndex(*(u32 *)(slot + 0x3f08) & 0xffff);
          func_01ffb12c(&actor->flags_004);
        }
      }
      index = index + 1;
    } while (index < 5);
    ActorChannel_SelectBuffer();
    DispatchModeUpdate();
  }
}
