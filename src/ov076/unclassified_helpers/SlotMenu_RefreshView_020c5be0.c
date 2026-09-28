#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x11f18];
    s32 scrollY;
} SlotMenu;

extern void *func_ov039_020bc1bc(void);
extern void func_ov076_020c74e4(SlotMenu *menu, int layerMode, s32 scrollY);
extern void func_ov027_020b8c94(void *session, int mode);
extern void func_ov076_020c7534(SlotMenu *menu, int layerMode);

void SlotMenu_RefreshView_020c5be0(SlotMenu *menu)
{
    void *session = func_ov039_020bc1bc();

    func_ov076_020c74e4(menu, 0, menu->scrollY);
    func_ov027_020b8c94(session, 0);
    func_ov076_020c7534(menu, 0);
}
