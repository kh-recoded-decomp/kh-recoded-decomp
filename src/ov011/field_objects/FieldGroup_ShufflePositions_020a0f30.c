#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x40];
    VecFx32 position;
} FieldObject;

typedef struct FieldGroup {
    u8 pad_00[0x46];
    u16 objectCount;
} FieldGroup;

extern void func_01ff8830(void *dst, int value, u32 size);
extern FieldObject *func_ov001_0207f4b4(FieldGroup *group, int index);
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern VecFx32 *func_ov011_020a0efc(int target, int count, VecFx32 *points, u8 *used);
extern void FieldObject_SetPositionAndSync_020a0954(FieldObject *object, const VecFx32 *position);

void FieldGroup_ShufflePositions_020a0f30(FieldGroup *group)
{
    u8 used[0x1a];
    VecFx32 positions[0x1a];
    int i = 0;
    int count = group->objectCount;

    func_01ff8830(used, 0, sizeof(used));
    for (; i < count; i++) {
        positions[i] = func_ov001_0207f4b4(group, i)->position;
    }
    for (i = 0; i < count; i++) {
        FieldObject *object = func_ov001_0207f4b4(group, i);
        FieldObject_SetPositionAndSync_020a0954(object, func_ov011_020a0efc(random_next_scaled_0202aa04(count - i), count, positions, used));
    }
}
