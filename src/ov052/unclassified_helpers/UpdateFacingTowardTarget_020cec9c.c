#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef BOOL (*TargetQuery)(int entity, VecFx32 *out);
typedef void (*AngleCallback)(int entity, u16 angle);

extern u16 func_ov052_020ceb7c(int entity);
extern VecFx32 *func_ov052_020ceb54(int entity);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern unsigned short FixedPointAtan2_020062bc(int vertical_component, int horizontal_component);
extern u32 func_ov001_0206db78(u32 index);
extern BOOL AlarmCallback_020a7504(u32 entry);
extern u32 func_ov021_020a7544(u32 entry);

void UpdateFacingTowardTarget_020cec9c(int entity, BOOL useEntry)
{
    VecFx32 target;
    VecFx32 delta;
    int angle = func_ov052_020ceb7c(entity);
    BOOL found;
    if (*(TargetQuery *)(entity + 0x228) != NULL) {
        found = (*(TargetQuery *)(entity + 0x228))(entity, &target);
    } else {
        found = FALSE;
    }
    if (found) {
        VEC_Subtract_01ff9e3c(&target, func_ov052_020ceb54(entity), &delta);
        angle = (u16)(FixedPointAtan2_020062bc(delta.x, delta.z) + 0x8000);
    } else if (useEntry) {
        u32 entry = func_ov001_0206db78(*(u8 *)(entity + 0x9b4));
        if (AlarmCallback_020a7504(entry)) {
            angle = func_ov021_020a7544(entry);
        }
    }
    if (*(AngleCallback *)(entity + 0x210) != NULL) {
        (*(AngleCallback *)(entity + 0x210))(entity, angle);
    }
}
