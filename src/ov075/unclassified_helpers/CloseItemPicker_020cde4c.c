#include "nitro/types.h"

#define REG_BG1OFS (*(volatile u32 *)0x04000014)

typedef struct ResourceContainer ResourceContainer;

typedef struct {
    u8 pad_0000[0x2bd8];
    u32 unlockFlags[0x10];
} SaveData;

typedef struct {
    u32 state;
    BOOL interactive;
    u8 pad_0008[0x10];
    ResourceContainer *layout;
    u8 pad_001c[0x4d84 - 0x1c];
    u8 listView[0x11e60 - 0x4d84];
    u16 stateFlags;
    u16 pad_11e62;
    u32 pendingUnlocks[0x10];
} ItemPicker;

extern char data_ov075_020d185c[];
extern SaveData *data_0205fe0c;
extern void NotifyBothOrOne_02001154(u32 a, u32 b, int index);
extern void SetStateFlagBits_020bc688(int clearMask, int setBits);
extern void SetUnlockableElementsVisible_020d0e64(ResourceContainer *layout, BOOL visible);
extern void SetLayoutElementVisible_020d0e4c(ResourceContainer *layout, s32 elementId, BOOL visible);
extern void func_ov039_020bdf10(void *listView, ResourceContainer *layout, int mode);
extern void CallStateWidget_020bc14c(int a, int b, int c, int d, int e);

void CloseItemPicker_020cde4c(ItemPicker *picker, BOOL closing)
{
    ResourceContainer *layout = picker->layout;
    u32 *src;
    u32 *dst;
    u32 *end;

    NotifyBothOrOne_02001154(1, (u32)data_ov075_020d185c, 0);
    SetStateFlagBits_020bc688(0xf, picker->stateFlags);
    SetUnlockableElementsVisible_020d0e64(layout, closing);
    SetLayoutElementVisible_020d0e4c(layout, 7, FALSE);
    SetLayoutElementVisible_020d0e4c(layout, 0x1b, FALSE);
    SetLayoutElementVisible_020d0e4c(layout, 0x1c, FALSE);
    SetLayoutElementVisible_020d0e4c(layout, 0, FALSE);
    SetLayoutElementVisible_020d0e4c(layout, 1, FALSE);
    func_ov039_020bdf10(picker->listView, layout, 0);
    picker->interactive = !closing;
    REG_BG1OFS = 0;
    if (closing) {
        CallStateWidget_020bc14c(9, 0, 0, 0x20, 0x18);
    }
    src = picker->pendingUnlocks;
    dst = data_0205fe0c->unlockFlags;
    end = dst + 0x10;
    for (; dst < end; src++, dst++) {
        *dst |= *src;
    }
}
