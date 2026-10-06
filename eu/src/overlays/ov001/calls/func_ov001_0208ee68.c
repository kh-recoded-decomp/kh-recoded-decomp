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
extern unsigned int ScriptVm_ReadOperandInt();
extern unsigned int _s32_div_f();
extern unsigned int ActorRegistry_GetEntityByIndex();

unsigned int func_ov001_0208ee68(void *vm,void *operands) {
  u32 actorId;
  int angle;
  ActorNode *actor;

  actorId = ScriptVm_ReadOperandInt(vm,operands);
  angle = ScriptVm_ReadOperandInt(vm,(void *)((int)operands + 8));
  actor = ActorRegistry_GetEntityByIndex(actorId & 0xffff);
  angle = _s32_div_f(angle << 0x10,0x168);
  *(short *)actor->unknown_082 = (short)angle;
  actor->flags_004 = actor->flags_004 | 0x20;
  return 1;
}
