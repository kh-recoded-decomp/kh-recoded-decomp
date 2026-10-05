#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xC4];
    s32 layout;
    s32 entryCount;
    s32 normalLayout;
    s32 normalCount;
    u8 pad_0D4[0x4];
    s32 commandCount;
    s32 commandEntry;
    u8 pad_0E0[0xC];
    s32 cursorIndex;
    u8 pad_0F0[0x4];
    s32 normalCursor;
    s32 commandCursor;
    u8 pad_0FC[0x8];
    s32 mode;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;
extern u16 data_ov001_0209ee82[][4];
extern u16 data_ov001_0209ee6a[][4];

extern void *GetSceneTagTracker_020711b0(void);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void func_ov001_02075e10(FieldMenu *menu, void *tracker, int mode);
extern void func_ov001_020769f4(FieldMenu *menu);
extern void GFXi_EnqueueCommand_02014090(int command, int offset, const void *src, int size);

void SetFieldMenuMode_02078360(int mode, BOOL refresh) {
    FieldMenu *menu = data_ov001_020a04b0.menu;
    void *tracker = GetSceneTagTracker_020711b0();

    if (!IsFieldFlag8Set_020728a4() && mode == 2) {
        return;
    }
    if (menu->mode == mode) {
        return;
    }
    switch (menu->mode) {
    case 0:
        menu->normalCursor = menu->cursorIndex;
        break;
    case 1:
        menu->commandCursor = menu->cursorIndex;
        break;
    case 2:
        break;
    }
    switch (mode) {
    case 0:
        menu->cursorIndex = menu->normalCursor;
        menu->layout = menu->normalLayout;
        menu->entryCount = menu->normalCount;
        break;
    case 1:
        if (menu->commandCount == 0) {
            return;
        }
        menu->cursorIndex = menu->commandCursor;
        menu->layout = 0xe;
        menu->entryCount = menu->commandCount;
        InvokeCallback40_020b8268(tracker, FindActiveRecordById_020b8184(tracker, 0x55));
        break;
    case 2:
        menu->cursorIndex = 0;
        menu->entryCount = menu->commandEntry;
        menu->layout = menu->entryCount;
        break;
    }
    menu->mode = mode;
    func_ov001_02075e10(menu, tracker, mode);
    if (refresh) {
        func_ov001_020769f4(menu);
    }
    GFXi_EnqueueCommand_02014090(0xf, 0x30, data_ov001_0209ee82[mode], 8);
    GFXi_EnqueueCommand_02014090(0xf, 0x130, data_ov001_0209ee6a[mode], 8);
    GFXi_EnqueueCommand_02014090(0xf, 0x150, data_ov001_0209ee6a[mode], 8);
}
