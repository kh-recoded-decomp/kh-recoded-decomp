#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void code();

extern void ApplyTimeScaledSpeed_020c7d28(int entity, fx32 targetSpeed);
extern void func_ov052_020c9834(int entity);
extern void func_ov052_020c76cc(int entity);
extern fx32 func_ov001_0206db44(void);
extern void func_ov052_020c967c(int entity);
extern void func_ov052_020c97a4(int entity);
extern void func_ov021_020a7fa4(int subObject, s32 a, s32 b);

/* Runs the actor's per-update subsystem refresh */
void RefreshActorState_020cce08(int entity)
{
    fx32 timeScale;

    ApplyTimeScaledSpeed_020c7d28(entity, *(fx32 *)(entity + 0x9f4));
    func_ov052_020c9834(entity);
    func_ov052_020c76cc(entity);
    timeScale = func_ov001_0206db44();
    if (*(code **)(entity + 0x1ec) != (code *)0) {
        (**(code **)(entity + 0x1ec))(entity, timeScale);
    }
    func_ov052_020c967c(entity);
    (**(code **)(entity + 0x9bc))(entity);
    func_ov052_020c97a4(entity);
    func_ov021_020a7fa4(entity + 0xb2c, *(s32 *)(entity + 0x75c), *(s32 *)(entity + 0x760));
}
