#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x50];
    u32 value1;
    u32 value2;
    u32 value3;
} ObjectState;

extern u32 ScriptCmd_ReadEntityParams();
extern void ReadFieldObjectSpawnExtraVector(ObjectState *obj, u32 source, u32 *cursor);
extern u32 GetFieldEntryPoolAtIndex(u32 value);
extern void SpawnFieldObjectTree();

u32 ScriptCmd_SpawnFieldObjectTreeWithExtraVector(u32 messageId, u32 arg1, u32 unused, u32 arg2)
{
    u32 context;
    ObjectState buffer;
    u32 cursor;
    u32 extra;

    cursor = arg1;
    extra = arg2;
    context = ScriptCmd_ReadEntityParams(&buffer, messageId, &cursor);
    ReadFieldObjectSpawnExtraVector(&buffer, messageId, &cursor);
    context = GetFieldEntryPoolAtIndex(context);
    SpawnFieldObjectTree(context, &buffer);
    return 1;
}
