#include "nitro/types.h"

typedef struct SlotPosition {
    s32 x;
    s32 y;
} SlotPosition;

extern int PXI_Init_0204f0b4(void *manager, int resource, int animation);
extern void func_0204f13c(void *manager, int slotIndex, SlotPosition *position);
extern void Slot_SetMode2Bit_0204f480(void *manager, int slotIndex, int mode);
extern void func_0204f178(void *manager, int slotIndex, int priority);
extern void func_0204f2e4(void *manager, int slotIndex);
extern void func_0204f204(void *manager, int slotIndex, int palette);
extern void func_0204f378(void *manager, int slotIndex, int enabled);

int CreateObjectSlot_020bdea4(void *manager, int animation, int resource, int x, int y, int mode,
                              int priority, int palette, int enabled) {
    int slotIndex = PXI_Init_0204f0b4(manager, resource, animation);
    SlotPosition position;
    position.x = x << 12;
    position.y = y << 12;
    func_0204f13c(manager, slotIndex, &position);
    Slot_SetMode2Bit_0204f480(manager, slotIndex, mode);
    func_0204f178(manager, slotIndex, (u8)priority);
    if (palette >= 0) {
        func_0204f2e4(manager, slotIndex);
        func_0204f204(manager, slotIndex, (u16)palette);
    }
    func_0204f378(manager, slotIndex, enabled);
    return slotIndex;
}
