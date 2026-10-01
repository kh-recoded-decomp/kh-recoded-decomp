#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *objManager;
} PopupManager;

extern PopupManager *g_popupManager_020c50e4;
extern void func_0204f204(void *objManager, int slotIndex, int value);
extern int func_0204f2c0(void *objManager, int slotIndex);
extern void func_0204f2e4(void *objManager, int slotIndex);
extern void func_0204f378(void *objManager, int slotIndex, int value);

void func_ov093_020c317c(int slotIndex, BOOL visible)
{
    void *objManager = g_popupManager_020c50e4->objManager;

    if (visible) {
        func_0204f204(objManager, slotIndex, 0);
        func_0204f2c0(objManager, slotIndex);
    } else {
        func_0204f2e4(objManager, slotIndex);
    }
    func_0204f378(objManager, slotIndex, visible);
}
