#include "nitro/types.h"

typedef struct AxisState {
    s32 value;
    u8 pad_04[0x10];
} AxisState;

typedef struct ActorManager {
    u8 pad_000[0x7A4];
    AxisState axes[2];
} ActorManager;

extern ActorManager *gActorSceneManager;
extern BOOL IsScreenModeIdle(void);
extern BOOL OpenFieldPanel(void);
extern int GetMainBrightnessSetting(void);
extern int GetSubBrightnessSetting(void);
extern int abs(int x);
extern int CmdOpenDialog_02088580(int script, int operand);

s32 WaitForFieldPanelAndCacheExtremeBrightness(void)
{
    ActorManager *manager;
    int axisIndex;

    manager = gActorSceneManager;
    if (IsScreenModeIdle() && OpenFieldPanel()) {
        manager->axes[0].value = GetMainBrightnessSetting();
        manager->axes[1].value = GetSubBrightnessSetting();
        for (axisIndex = 0; axisIndex < 2; axisIndex++) {
            if (abs(manager->axes[axisIndex].value) != 16) {
                manager->axes[axisIndex].value = 0;
            }
        }
        return (s32)CmdOpenDialog_02088580;
    }
    return 0;
}
