#include "nitro/types.h"

typedef struct StageObject {
    u8 pad_000[0x10];
    u16 active;
    u8 pad_012[0x1B6];
} StageObject;

typedef struct StageGroup {
    u8 pad_00[0xA];
    s16 first;
    s16 last;
} StageGroup;

typedef struct StageObjectParams {
    u8 pad_00[0x28];
    u16 flags;
    u8 pad_2A[0x1E];
} StageObjectParams;

typedef struct StageManager {
    u8 pad_00000[0x210];
    StageObject *objects;
    u8 pad_00214[0x18BD2];
    u16 groupCount;
} StageManager;

extern StageManager *data_ov001_020a0508;

extern StageGroup *GetStageObjectHandle_0209c0c4(u32 id);
extern void func_01ff8830(void *dest, int value, u32 size);
extern void func_ov001_020958f4(StageObject *object, StageObjectParams *params);

void ResetStageGroupObjects_0209cae0(u32 groupId)
{
    StageManager *manager = data_ov001_020a0508;
    StageGroup *group;
    int i;
    StageObject *object;
    StageObjectParams params;

    if (groupId >= manager->groupCount) {
        return;
    }
    group = GetStageObjectHandle_0209c0c4((u16)(groupId + 1));
    if (group == NULL) {
        return;
    }
    for (i = group->first; i <= group->last; i++) {
        object = &manager->objects[i];
        if (object->active != 0) {
            func_01ff8830(&params, 0, sizeof(params));
            params.flags |= 0x200;
            func_ov001_020958f4(object, &params);
        }
    }
}
