#include "nitro/types.h"

typedef struct MeshRoomData {
    s8 unk_00;
    s8 area;
    s8 room;
    s8 variant;
} MeshRoomData;

typedef struct MeshNamedEntry {
    u8 pad_00[0xc];
    u8 visible;
    u8 pad_0d[3];
    MeshRoomData *data;
} MeshNamedEntry;

typedef struct DoorObject {
    u8 pad_00[0x1c];
    u8 *roomId;
    u8 area;
    u8 variant;
    u16 state;
} DoorObject;

extern const char data_ov001_0209ea70[];
extern const char data_ov001_0209ea64[];
extern const char data_ov001_0209ea78[];
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern int Strlen_02021e44(const char *str);
extern void ApplyToNamedCollisionFaces_020680fc(const char *name, int nameLength, BOOL enable);
extern MeshNamedEntry *FindWorldMeshEntryByName_02036288(const char *name);
extern void SetWorldMeshEntryDataByName_020363a4(const char *name, const void *src, u32 size);

void SyncDoorMeshState_020671e0(DoorObject *door)
{
    u32 room;
    u32 openState;
    MeshNamedEntry *entry;
    MeshRoomData *current;
    char meshName[8];
    MeshRoomData data;
    char collisionName[16];

    room = *door->roomId;
    openState = door->state & 3;
    OS_SPrintf_02002428(collisionName, data_ov001_0209ea70, data_ov001_0209ea64, room);
    ApplyToNamedCollisionFaces_020680fc(collisionName, Strlen_02021e44(collisionName), openState == 0);
    OS_SPrintf_02002428(meshName, data_ov001_0209ea70, data_ov001_0209ea78, room);
    if (openState == 0) {
        entry = FindWorldMeshEntryByName_02036288(meshName);
        if (entry != NULL) {
            entry->visible = 0;
        }
        return;
    }
    entry = FindWorldMeshEntryByName_02036288(meshName);
    if (entry == NULL) {
        return;
    }
    entry->visible = 1;
    current = entry->data;
    if (current != NULL && current->area == door->area && current->room == room && current->variant == door->variant) {
        return;
    }
    data.area = door->area;
    data.room = room;
    data.variant = door->variant;
    data.unk_00 = 0;
    SetWorldMeshEntryDataByName_020363a4(meshName, &data, sizeof(MeshRoomData));
}
