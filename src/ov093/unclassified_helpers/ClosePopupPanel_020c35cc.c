#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int slotIndex;
} PopupManager;

extern PopupManager *g_popupManager_020c50e4;
extern void SetBgSubLayerVisible_020c3b5c(void *machine, BOOL visible);
extern void func_ov093_020c317c(int slotIndex, BOOL visible);
extern void func_ov093_020c2f1c(void *work);
extern void StateMachine_SetState_020c3bc4(void *machine, int state);

void ClosePopupPanel_020c35cc(void *machine)
{
    SetBgSubLayerVisible_020c3b5c(machine, FALSE);
    func_ov093_020c317c(g_popupManager_020c50e4->slotIndex, FALSE);
    func_ov093_020c2f1c(machine);
    StateMachine_SetState_020c3bc4(machine, 0);
}
