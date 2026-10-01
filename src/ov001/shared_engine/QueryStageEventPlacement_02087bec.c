#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventPlacement {
    VecFx32 position;
    u32 unkC;
    u16 direction;
    u16 unk12;
} EventPlacement;

extern int data_ov001_0209f2c8;
extern u8 *GetStageEventRecord_0209c0ec(u32 id);
extern void MI_CpuFill8_01ff8830(void *dest, u8 value, u32 size);
extern int func_ov001_0209661c(u8 *record, int arg, EventPlacement *placement);

int QueryStageEventPlacement_02087bec(u32 id, int arg, VecFx32 *position, u16 *direction) {
    EventPlacement placement;
    u8 *record;
    int result;

    if (data_ov001_0209f2c8 != -1) {
        record = GetStageEventRecord_0209c0ec(id);
        MI_CpuFill8_01ff8830(&placement, 0, sizeof(EventPlacement));
        if (record != NULL) {
            result = func_ov001_0209661c(record, arg, &placement);
            if (position != NULL) {
                *position = placement.position;
            }
            if (direction != NULL) {
                *direction = placement.direction;
            }
            return result;
        }
    }
    return 0;
}
