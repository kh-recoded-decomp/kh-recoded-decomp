#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct {
    u8 pad_00000[0x74];
    s32 dialogOpen;
    u8 pad_00078[0x131a4 - 0x78];
    ResourceContainer *layout;
    u8 pad_131a8[0x13e7c - 0x131a8];
    u8 unk_13E7C;
    u8 pad_13e7d[0x13ea0 - 0x13e7d];
    s32 unk_13EA0;
    u8 pad_13ea4[0x174f8 - 0x13ea4];
    s32 pendingAction;
    u8 pad_174fc[0x17518 - 0x174fc];
    s32 unk_17518;
} MatrixMenu;

extern void *data_0205fe0c;
extern void SetLayoutElementVisible_020d0e4c(ResourceContainer *layout, s32 elementId, BOOL visible);
extern void SetUnlockableElementsVisible_020d0e64(ResourceContainer *layout, BOOL visible);
extern s32 func_ov075_020cc9fc(MatrixMenu *menu, s32 mode, s32 arg);
extern void func_ov075_020c6358(MatrixMenu *menu, BOOL flag);
extern void func_ov075_020c4370(MatrixMenu *menu);
extern void func_ov073_020c2ca4(int state, int parameter);
extern void func_ov073_020c1eb4(void *save, int arg);

void OnMessageDialogClosed_020c8d30(MatrixMenu *menu)
{
    s32 action = menu->pendingAction;
    BOOL flag = FALSE;

    SetLayoutElementVisible_020d0e4c(menu->layout, 0x2a, FALSE);
    menu->dialogOpen = func_ov075_020cc9fc(menu, 0, 0);
    if (menu->dialogOpen == 0 && action != 0) {
        switch (action) {
        case 1:
            if (menu->unk_13E7C != 0) {
                break;
            }
            goto resume;
        case 2:
            if (menu->unk_13E7C == 0) {
                flag = TRUE;
            }
            func_ov075_020c6358(menu, flag);
            func_ov073_020c2ca4(3, -1);
            func_ov073_020c1eb4(data_0205fe0c, 0);
            func_ov075_020cc9fc(menu, 1, 0);
            break;
        case 3:
            if (menu->unk_13EA0 == 1) {
                break;
            }
            menu->unk_17518 = 1;
        resume:
            func_ov075_020c4370(menu);
            break;
        }
        menu->pendingAction = 0;
    }
    if (menu->dialogOpen == 0 && action != 3) {
        SetUnlockableElementsVisible_020d0e64(menu->layout, TRUE);
    }
}
