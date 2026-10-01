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
extern unsigned int ActorSlot_SetFlag8ByIndex_02036120();
extern unsigned int RebindAnimTracks_020809d0();
extern unsigned int func_0202f4e8();
extern unsigned int func_02036810();
extern unsigned int func_02036924();
extern unsigned int func_arm9_02036240();
extern unsigned int func_ov018_020a1ebc();
extern unsigned int func_ov018_020a333c();
extern unsigned int func_ov018_020a3404();

void func_ov018_020a3484(int work) {
  ActorNode *actor;
  int slot;

  func_ov018_020a3404();
  actor = func_arm9_02036240((u32)*(u8 *)(work + 0x32));
  RebindAnimTracks_020809d0(&actor->flags_004,(int)*(char *)(work + 0x47),0);
  func_0202f4e8(&actor->flags_004);
  ActorSlot_SetFlag8ByIndex_02036120((u32)*(u8 *)(work + 0x32),1);
  slot = func_02036810(*(u8 *)(work + 0x32));
  if ((*(u16 *)(slot + 8) & 0x100) == 0) {
    func_02036924((u32)*(u8 *)(work + 0x32));
  }
  func_ov018_020a333c(work,0);
  func_ov018_020a1ebc(work);
  *(u16 *)(work + 0x30) = *(u16 *)(work + 0x30) | 0x10;
  *(u16 *)(work + 0x30) = *(u16 *)(work + 0x30) | 8;
}
