#include "nitro/types.h"

typedef struct AxisState {
    s32 value;
    u8 pad_04[0x10];
} AxisState;

typedef struct ActorManager {
    u8 pad_000[0x7A4];
    AxisState axes[2];
} ActorManager;

extern ActorManager *data_ov001_020a0500;
extern BOOL IsScreenModeIdle(void);
extern BOOL OpenFieldPanel(void);
extern int func_02029f5c(void);
extern int func_02029f6c(void);
extern int abs(int x);
extern int func_ov001_02088580(int script, int operand);

s32 func_ov001_020882d8(void)
{
    ActorManager *manager;
    int axisIndex;

    manager = data_ov001_020a0500;
    if (IsScreenModeIdle() && OpenFieldPanel()) {
        manager->axes[0].value = func_02029f5c();
        manager->axes[1].value = func_02029f6c();
        for (axisIndex = 0; axisIndex < 2; axisIndex++) {
            if (abs(manager->axes[axisIndex].value) != 16) {
                manager->axes[axisIndex].value = 0;
            }
        }
        return (s32)func_ov001_02088580;
    }
    return 0;
}
