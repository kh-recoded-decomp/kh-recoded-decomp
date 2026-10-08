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
extern unsigned int Obj_SetPosition();
extern unsigned int ActorSlot_GetByIndex();
extern unsigned int TransitionRecordSlot();
extern unsigned int ClearRecordSlotFlag();
extern unsigned int ActorRegistry_GetEntityByIndex();
extern unsigned int UpdateFieldObjectHighlight();

void func_ov016_020a2688(int work,int enabled) {
  int slot;
  ActorNode *entity;

  slot = ActorSlot_GetByIndex(*(u8 *)(work + 0x32));
  if (enabled == 0) {
    UpdateFieldObjectHighlight(work,0);
    if ((*(u16 *)(slot + 8) & 0x100) != 0) {
      ClearRecordSlotFlag((u32)*(u8 *)(work + 0x32));
    }
    *(u32 *)(work + 0xc0) = *(u32 *)(work + 0xc0) & 0xfffffffe;
    return;
  }
  UpdateFieldObjectHighlight(work,1);
  entity = ActorRegistry_GetEntityByIndex((u32)*(u8 *)(work + 0x32));
  Obj_SetPosition(entity,(void *)(work + 0x38));
  if ((*(u16 *)(slot + 8) & 0x100) == 0) {
    TransitionRecordSlot((u32)*(u8 *)(work + 0x32));
  }
  *(u32 *)(work + 0xc0) = *(u32 *)(work + 0xc0) | 1;
}
