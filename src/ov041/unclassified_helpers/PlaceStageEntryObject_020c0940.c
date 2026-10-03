#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u16 drawFlags;
    u8 pad_006[0x7a];
    s16 tilt;
} StageObject;

typedef struct {
    u8 pad_000[2];
    u8 column;
    u8 row;
    u8 pad_004[4];
    u32 flags;
    u8 pad_00c[0x160];
    StageObject object;
    u8 pad_1f0[0x2c4];
} StageEntry;

typedef struct {
    u8 pad_00[0x14];
    StageEntry *entries;
} StageWork;

extern u8 *data_ov035_020bc4e0;
extern void func_ov041_020c0ef0(int index, u8 slot);
extern void func_ov041_020c1d18(int index, u8 slot);
extern void func_ov041_020c18cc(int index, u8 slot);
extern void GetStageGridPosition_020c2b5c(VecFx32 *out, int column, int row);
extern void Obj_SetPosition_0203569c(StageObject *object, const VecFx32 *pos);

void PlaceStageEntryObject_020c0940(int index, int slot) {
    StageEntry *entry = &(*(StageWork **)(data_ov035_020bc4e0 + 0xb8))->entries[index];
    s16 tilt;
    VecFx32 pos;

    func_ov041_020c0ef0(index, slot);
    if (slot == 0xff) {
        func_ov041_020c1d18(index, slot);
    } else {
        func_ov041_020c18cc(index, slot);
    }
    if (entry->flags & 1) {
        tilt = 0x3ffc;
    } else {
        tilt = -0x3ffc;
    }
    GetStageGridPosition_020c2b5c(&pos, entry->column, entry->row);
    Obj_SetPosition_0203569c(&entry->object, &pos);
    if ((entry->object.flags & 0x20) == 0) {
        entry->object.tilt = tilt;
        entry->object.drawFlags |= 0x20;
    }
}
