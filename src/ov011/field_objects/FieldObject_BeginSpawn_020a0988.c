#include "nitro/types.h"

typedef struct ObjectClass {
    u8 pad_00[0x50];
    s32 result;
} ObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    ObjectClass *objectClass;
    u8 pad_0c[0x34];
    u32 position[3];
    u8 pad_4c[0x10];
    u8 spawnCommand[4];
} FieldObject;

extern void func_ov011_020a06e8(FieldObject *object, int state);
extern void RunSpawnCommand_020a0afc(void *command, FieldObject *object);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, u32 *position, u32 flags);

s32 FieldObject_BeginSpawn_020a0988(FieldObject *object)
{
    ObjectClass *objectClass = object->objectClass;
    func_ov011_020a06e8(object, 1);
    RunSpawnCommand_020a0afc(object->spawnCommand, object);
    SpawnSoundSlot_0204da8c(0, 0x2d, object->position, 0);
    return objectClass->result;
}
