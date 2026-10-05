#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u16 drawFlags;
    u8 pad_006[0x7a];
    s16 tilt;
} StageObject;

typedef struct {
    u8 kind;
    u8 pad_001;
    u8 column;
    u8 row;
    u8 pad_004[4];
    u32 flags;
    u8 pad_00c[0x120];
    fx32 groundHeight;
    u8 pad_130[0x3c];
    StageObject object;
    u8 pad_1f0[0x24];
    VecFx32 position;
    u8 pad_220[0x110];
    void *resource;
    u8 pad_334[0x180];
} StageEntry;

typedef struct {
    u8 pad_00[0x14];
    StageEntry *entries;
} StageWork;

typedef struct {
    u8 pad_00[0x3e];
    u8 kind;
} SpawnParams;

extern u8 *data_ov035_020bc4e0;
extern u8 data_ov041_020cf7a0[];
extern void func_ov041_020c14e8(int index, SpawnParams *params);
extern void SpawnStageEntryActor(int index, u8 kind);
extern void func_ov041_020bd48c(u8 kind, void *resource);
extern void GetStageGridPosition(VecFx32 *out, int column, int row);
extern void Obj_SetPosition(StageObject *object, const VecFx32 *pos);

void SpawnStageEntry(int index, SpawnParams *params) {
    StageEntry *entry = &(*(StageWork **)(data_ov035_020bc4e0 + 0xb8))->entries[index];
    int tilt;
    VecFx32 pos;
    VecFx32 gridPos;

    if (params->kind == 0x63) {
        params->kind = 0xfd;
    }
    func_ov041_020c14e8(index, params);
    SpawnStageEntryActor(index, params->kind);
    if (entry->kind != 0xfd) {
        func_ov041_020bd48c(entry->kind, entry->resource);
    }
    if (entry->flags & 1) {
        if (entry->kind == 0xfd) {
            tilt = 0x3ffc;
        } else {
            tilt = (0x5a - data_ov041_020cf7a0[entry->kind]) * 0xb6;
        }
    } else {
        tilt = -0x3ffc;
    }
    GetStageGridPosition(&gridPos, entry->column, entry->row);
    Obj_SetPosition(&entry->object, &gridPos);
    if ((entry->object.flags & 0x20) == 0) {
        entry->object.tilt = tilt;
        entry->object.drawFlags |= 0x20;
    }
    pos = entry->position;
    pos.y += entry->groundHeight;
    Obj_SetPosition(&entry->object, &pos);
}
