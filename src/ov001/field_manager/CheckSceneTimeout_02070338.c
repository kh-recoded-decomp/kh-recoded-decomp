#include "nitro/types.h"

typedef u64 OSTick;

typedef struct SceneTimer {
    u8 pad_00[0x20];
    OSTick duration;
    OSTick startTick;
} SceneTimer;

typedef struct FieldManager {
    u8 pad_000[0x550];
    SceneTimer timer;
} FieldManager;

extern OSTick OS_GetTick_02003fd4(void);
extern void func_ov001_02071f58(void);

void CheckSceneTimeout_02070338(FieldManager *manager)
{
    SceneTimer *timer = &manager->timer;

    if (timer->duration != 0) {
        if (OS_GetTick_02003fd4() - timer->startTick >= timer->duration) {
            func_ov001_02071f58();
        }
    }
}
