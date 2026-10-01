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
extern int data_ov035_020bc4e4;
extern int GetMaterialAlpha_0201a810();
extern int SetMaterialAlpha_0201a64c();
extern int SetMaterialPolygonId_0201a5d4();
extern int func_arm9_0201a55c();

void func_ov035_020bb448(int index) {
  int work;
  u32 previousAlpha;
  char *entry;
  int entries;

  work = data_ov035_020bc4e4;
  index = index * 4;
  entries = *(int *)(data_ov035_020bc4e4 + 0x10c);
  entry = (char *)(entries + index);
  previousAlpha = GetMaterialAlpha_0201a810
                    (*(void **)(data_ov035_020bc4e4 + 0x78),(int)*(char *)(entries + index));
  SetMaterialAlpha_0201a64c
            (*(void **)(work + 0x78),(int)*(char *)(entries + index),(int)entry[2]);
  SetMaterialPolygonId_0201a5d4(*(void **)(work + 0x78),(int)*(char *)(entries + index),0x28)
  ;
  if (entry[2] == '\0') {
    func_arm9_0201a55c(*(ModelResource **)(work + 0x78),(int)*entry,0);
    return;
  }
  if (previousAlpha == 0) {
    func_arm9_0201a55c(*(ModelResource **)(work + 0x78),(int)*entry,2);
  }
}
