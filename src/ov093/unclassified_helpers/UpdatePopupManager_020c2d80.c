#include "nitro/types.h"

typedef struct {
    int state;
    u32 flags;
    int frameCount;
} StateMachine;

typedef struct {
    u8 pad_000[0x2c];
    StateMachine machine;
    u8 pad_038[0x26c - 0x38];
    int pendingCount;
} PopupManager;

typedef void (*PopupStateHandler)(StateMachine *machine);

extern PopupManager *g_popupManager_020c50e4;
extern const PopupStateHandler data_ov093_020c3e54[];
extern int func_ov093_020c3bd4(StateMachine *machine);
extern void func_01ff8740(int value, void *dest, int size);
extern void StateMachine_SetState_020c3bc4(StateMachine *machine, int state);

int UpdatePopupManager_020c2d80(void)
{
    PopupManager *manager = g_popupManager_020c50e4;
    PopupStateHandler handler = data_ov093_020c3e54[func_ov093_020c3bd4(&manager->machine)];

    if (handler != NULL) {
        handler(&manager->machine);
    }
    if (g_popupManager_020c50e4->pendingCount > 0 && func_ov093_020c3bd4(&manager->machine) >= 0) {
        func_01ff8740(0, &g_popupManager_020c50e4->machine, 0x60);
        StateMachine_SetState_020c3bc4(&g_popupManager_020c50e4->machine, 1);
    }
    return 0;
}
