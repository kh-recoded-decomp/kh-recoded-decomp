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
extern unsigned int Obj_SetPosition();
extern unsigned int RebindAnimTracks();
extern unsigned int Flags16_ClearBit1();
extern unsigned int IndexedBytes_SetAt10();
extern unsigned int ApplyRecordTableEntry2();
extern unsigned int ApplyRecordTableEntry5();
extern unsigned int ActorSlot_GetByIndex();
extern unsigned int SetActorExtraPosition();
extern unsigned int ActorRegistry_GetEntityByIndex();
extern unsigned int func_ov001_0207f078();
extern unsigned int func_ov001_020807b4();
extern unsigned int IsNodeFlagBitClear();

void func_ov020_020a20b0(int work,int mode,u16 *actorCounter,int value) {
  ActorNode *entity;
  int result;
  u8 configuration [20];

  if (mode == 2) {
    func_ov001_020807b4
              (*(unsigned int *)(work + 8),*(u8 *)(*(int *)(work + 4) + 0x59),
               *(u8 *)(work + 0x33),*(u8 *)(work + 0x32),configuration,3,
               *(char *)(work + 0x49) * 0x1800,*(char *)(work + 0x4a) * 0x1800,
               *(char *)(work + 0x4b) * 0x1800,0,1,0);
    ApplyRecordTableEntry2((u32)*(u8 *)(work + 0x32),(int)actorCounter,value,4);
    *actorCounter = *actorCounter + 1;
    entity = ActorRegistry_GetEntityByIndex((u32)*(u8 *)(work + 0x32));
    Obj_SetPosition(entity,(void *)(work + 0x38));
    if ((entity->flags_000 & 0x20) == 0) {
      entity->halfword_080 = 0;
      entity->flags_004 = entity->flags_004 | 0x20;
    }
    RebindAnimTracks(&entity->flags_004,(int)*(char *)(work + 0x47),0);
    Flags16_ClearBit1(&entity->flags_004);
    result = IsNodeFlagBitClear(work);
    if (result != 0) {
      ApplyRecordTableEntry5((u32)*(u8 *)(work + 0x32),0,0);
    }
    result = IsNodeFlagBitClear(work);
    ActorSlot_SetFlag8ByIndex((u32)*(u8 *)(work + 0x32),result);
    result = ActorSlot_GetByIndex(*(u8 *)(work + 0x32));
    *(u16 *)(result + 8) = *(u16 *)(result + 8) | 0x200;
    IndexedBytes_SetAt10(entity[1].unknown_006 + 0x46,1,4);
    IndexedBytes_SetAt10(entity[1].unknown_006 + 0x46,3,0xc);
    func_ov001_0207f078(0xc);
    SetActorExtraPosition((u32)*(u8 *)(work + 0x32),work,7);
    *(u16 *)(work + 0x30) = *(u16 *)(work + 0x30) | 4;
  }
}
