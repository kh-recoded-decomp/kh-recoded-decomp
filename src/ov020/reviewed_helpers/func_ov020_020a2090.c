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
extern unsigned int Obj_SetPosition_0203569c();
extern unsigned int RebindAnimTracks_020809d0();
extern unsigned int func_0202f4e8();
extern unsigned int func_02034050();
extern unsigned int func_020358b0();
extern unsigned int func_020359f8();
extern unsigned int func_02036810();
extern unsigned int func_020369c8();
extern unsigned int func_arm9_02036240();
extern unsigned int func_ov001_0207f050();
extern unsigned int func_ov001_0208078c();
extern unsigned int func_ov001_020872b8();

void func_ov020_020a2090(int work,int mode,u16 *actorCounter,int value) {
  ActorNode *entity;
  int result;
  u8 configuration [20];

  if (mode == 2) {
    func_ov001_0208078c
              (*(unsigned int *)(work + 8),*(u8 *)(*(int *)(work + 4) + 0x59),
               *(u8 *)(work + 0x33),*(u8 *)(work + 0x32),configuration,3,
               *(char *)(work + 0x49) * 0x1800,*(char *)(work + 0x4a) * 0x1800,
               *(char *)(work + 0x4b) * 0x1800,0,1,0);
    func_020358b0((u32)*(u8 *)(work + 0x32),(int)actorCounter,value,4);
    *actorCounter = *actorCounter + 1;
    entity = func_arm9_02036240((u32)*(u8 *)(work + 0x32));
    Obj_SetPosition_0203569c(entity,(void *)(work + 0x38));
    if ((entity->flags_000 & 0x20) == 0) {
      entity->halfword_080 = 0;
      entity->flags_004 = entity->flags_004 | 0x20;
    }
    RebindAnimTracks_020809d0(&entity->flags_004,(int)*(char *)(work + 0x47),0);
    func_0202f4e8(&entity->flags_004);
    result = func_ov001_020872b8(work);
    if (result != 0) {
      func_020359f8((u32)*(u8 *)(work + 0x32),0,0);
    }
    result = func_ov001_020872b8(work);
    ActorSlot_SetFlag8ByIndex_02036120((u32)*(u8 *)(work + 0x32),result);
    result = func_02036810(*(u8 *)(work + 0x32));
    *(u16 *)(result + 8) = *(u16 *)(result + 8) | 0x200;
    func_02034050(entity[1].unknown_006 + 0x46,1,4);
    func_02034050(entity[1].unknown_006 + 0x46,3,0xc);
    func_ov001_0207f050(0xc);
    func_020369c8((u32)*(u8 *)(work + 0x32),work,7);
    *(u16 *)(work + 0x30) = *(u16 *)(work + 0x30) | 4;
  }
}
