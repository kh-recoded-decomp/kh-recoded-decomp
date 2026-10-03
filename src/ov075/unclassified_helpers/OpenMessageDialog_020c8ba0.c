#include "nitro/types.h"

typedef char *va_list;
typedef struct ResourceContainer ResourceContainer;

typedef struct DialogCallback {
    void (*func)(void *arg);
    void *arg;
} DialogCallback;

typedef struct DialogSize {
    u16 width;
    s16 height;
} DialogSize;

typedef union DialogSizeResult {
    u32 raw;
    DialogSize size;
} DialogSizeResult;

typedef struct MatrixMenu {
    u8 pad_00000[7];
    u8 textRefreshFrames;
    u8 pad_00008[0x74 - 8];
    s32 dialogOpen;
    u8 pad_00078[0x4ee0 - 0x78];
    u8 messageTable[0x8020 - 0x4ee0];
    u8 dialog[0x11c64 - 0x8020];
    DialogCallback onClose;
    DialogCallback onCancel;
    DialogCallback onConfirm;
    u16 buttonFlags[4];
    u8 pad_11c84[0x11fac - 0x11c84];
    const void *descriptionText;
    u8 pad_11fb0[0x131a4 - 0x11fb0];
    ResourceContainer *layout;
    u8 pad_131a8[0x174f8 - 0x131a8];
    s32 pendingAction;
} MatrixMenu;

extern char data_ov075_020d18e4[];

extern void func_ov027_020ba31c(void *table, int messageId, char *dst, int size, va_list args);
extern DialogSizeResult func_ov075_020cf368(void *dialog, int buttons, const char *text);
extern void func_ov075_020cf430(void *dialog, int buttons, int x, u16 y, u16 width, u16 height, const char *text);
extern void OnMessageDialogClosed_020c8d30(void *menu);
extern void DrawDialogText_020cfa50(void *menu);
extern void SetMatrixInputDisabled_020c8de8(void *menu);
extern void SetUnlockableElementsVisible_020d0e64(ResourceContainer *layout, BOOL visible);

void OpenMessageDialog_020c8ba0(MatrixMenu *menu, int messageId, int dialogType, int position, int cancelable, va_list args)
{
    DialogSizeResult result;
    int buttons;
    int y;
    DialogCallback onClose;
    DialogCallback onCancel;
    DialogCallback onConfirm;

    if (dialogType != 0 && dialogType != 3) {
        buttons = 2;
    } else {
        buttons = 1;
    }
    func_ov027_020ba31c(menu->messageTable, messageId, data_ov075_020d18e4, 0x100, args);
    result = func_ov075_020cf368(menu->dialog, buttons, data_ov075_020d18e4);

    onClose.func = OnMessageDialogClosed_020c8d30;
    onClose.arg = menu;
    menu->onClose = onClose;

    onCancel.func = DrawDialogText_020cfa50;
    onCancel.arg = cancelable ? menu : NULL;
    menu->onCancel = onCancel;

    if (buttons == 2) {
        onConfirm.func = SetMatrixInputDisabled_020c8de8;
        onConfirm.arg = menu;
        menu->onConfirm = onConfirm;
        menu->buttonFlags[0] = 1;
        menu->buttonFlags[1] = 1;
        menu->buttonFlags[2] = 1;
        menu->buttonFlags[3] = 3;
    }
    menu->pendingAction = dialogType;

    if (position < 0) {
        y = (0xb - result.size.height) / 2 + 0xb;
        if (y + result.size.height > 0x16) {
            y = 0x16 - result.size.height;
        }
    } else if (position > 0) {
        y = (0xb - result.size.height) / 2;
        if (y < 0) {
            y = 0;
        }
    } else {
        y = (0x14 - result.size.height) / 2;
    }
    func_ov075_020cf430(menu->dialog, buttons, 0, y, result.size.width, result.size.height, data_ov075_020d18e4);
    menu->dialogOpen = 1;
    menu->descriptionText = NULL;
    menu->textRefreshFrames = 1;
    SetUnlockableElementsVisible_020d0e64(menu->layout, FALSE);
}
