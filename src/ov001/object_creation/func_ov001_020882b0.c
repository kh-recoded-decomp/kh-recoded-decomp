#include "nitro/types.h"

typedef struct AxisState {
    s32 value;
    u8 pad_04[0x10];
} AxisState;

typedef struct ActorManager {
    u8 pad_000[0x7A4];
    AxisState axes[2];
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;
extern BOOL func_ov001_0206a814(void);
extern BOOL OpenFieldPanel_020717e4(void);
extern int func_02029f48(void);
extern int func_02029f58(void);
extern int abs_0202198c(int x);
extern int CmdOpenDialog_02088558(int script, int operand);

s32 func_ov001_020882b0(void)
{
    ActorManager *manager;
    int axisIndex;

    manager = g_actorManager_020a04e0;
    if (func_ov001_0206a814() && OpenFieldPanel_020717e4()) {
        manager->axes[0].value = func_02029f48();
        manager->axes[1].value = func_02029f58();
        for (axisIndex = 0; axisIndex < 2; axisIndex++) {
            if (abs_0202198c(manager->axes[axisIndex].value) != 16) {
                manager->axes[axisIndex].value = 0;
            }
        }
        return (s32)CmdOpenDialog_02088558;
    }
    return 0;
}
