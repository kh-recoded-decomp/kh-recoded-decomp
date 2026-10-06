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
extern unsigned int ActorSlot_SetFlag8ByIndex();
extern unsigned int RebindAnimTracks();
extern unsigned int Flags16_ClearBit1();
extern unsigned int ActorSlot_GetByIndex();
extern unsigned int TransitionRecordSlot();
extern unsigned int ActorRegistry_GetEntityByIndex();
extern unsigned int ResetKindDirection();
extern unsigned int func_ov018_020a335c();
extern unsigned int func_ov018_020a3424();

void func_ov018_020a34a4(int work) {
  ActorNode *actor;
  int slot;

  func_ov018_020a3424();
  actor = ActorRegistry_GetEntityByIndex((u32)*(u8 *)(work + 0x32));
  RebindAnimTracks(&actor->flags_004,(int)*(char *)(work + 0x47),0);
  Flags16_ClearBit1(&actor->flags_004);
  ActorSlot_SetFlag8ByIndex((u32)*(u8 *)(work + 0x32),1);
  slot = ActorSlot_GetByIndex(*(u8 *)(work + 0x32));
  if ((*(u16 *)(slot + 8) & 0x100) == 0) {
    TransitionRecordSlot((u32)*(u8 *)(work + 0x32));
  }
  func_ov018_020a335c(work,0);
  ResetKindDirection(work);
  *(u16 *)(work + 0x30) = *(u16 *)(work + 0x30) | 0x10;
  *(u16 *)(work + 0x30) = *(u16 *)(work + 0x30) | 8;
}
