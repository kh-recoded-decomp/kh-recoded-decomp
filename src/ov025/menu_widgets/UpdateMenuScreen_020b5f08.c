#include "nitro/types.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

extern u32 g_uiContext_020b7760;
extern u16 data_02060500;

extern s32 GetClampedPaletteSlot_02073598(void);
extern int func_ov025_020b74bc(u32 list);
extern void ScrollListToRow_020b7468(u32 list, int targetRow);
extern int CopyRecentInputRecords_0202b6d0(TouchSample *records);
extern u32 func_ov001_0207b6d4(void);
extern int func_02029f58(void);
extern void UpdateListScrollAnimation_020b7268(u32 list, TouchSample *touch, int input);
extern u32 func_ov001_0207b5f4(void);
extern BOOL IsFieldPanelHidden_0207187c(void);
extern unsigned int func_ov001_02064490(void);
extern int func_ov001_02064784(void);
extern BOOL func_ov001_020645c8(u32 value);
extern int *func_ov027_020b90a4(u32 obj, int id);
extern void SetEntrySlotsVisible_020b9580(u32 obj, int *entry, int visible);
extern int CopySourceBlock_020b9f7c(TouchSample *block);
extern void func_ov027_020b7dd4(u32 menu);
extern void UpdateWidgetRootAndResetList_020b8c80(u32 root, int keys);
extern void func_ov027_020b9e60(void *table);
extern int GetAvailableMenuEntryIndex_020b763c(u32 list);
extern void CallVirtualHandlerSlot1_02001574(void *object, int arg);
extern void *func_ov001_0207b748(void);
extern u32 func_ov027_020ba2a8(void *messages, int index);
extern u32 func_ov001_0207b6e0(s32 index);
extern void *GetFieldFont2_020711d4(void);
extern void func_020016f0(void *context, u32 x, u32 y, u32 color, u32 flags, u32 text, void *font, int maxWidth);
extern void Text_UploadTileBuffer_02001520(void *context);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern void *func_ov001_0207123c(void);
extern void ClearTileTableRowDirty_020b9e30(void *table, int id);
extern void SetSecondaryBrightness_02029ed0(int value);
extern void func_ov025_020b7658(u32 list, int arg);

int UpdateMenuScreen_020b5f08(void)
{
    u32 menu = g_uiContext_020b7760;
    TouchSample block;
    TouchSample records[4];
    int i;
    int last;
    int found;
    int index;
    void *tileTable;

    if (GetClampedPaletteSlot_02073598() != func_ov025_020b74bc(menu + 0x64f4)) {
        ScrollListToRow_020b7468(menu + 0x64f4, GetClampedPaletteSlot_02073598());
    }
    if (*(u8 *)(menu + 0x64e9) != 0) {
        found = -1;
        last = CopyRecentInputRecords_0202b6d0(records) - 1;
        for (i = last; i >= 0; i--) {
            if (records[i].validity == 0) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            found = last;
        }
        if (func_ov001_0207b6d4()) {
            records[found].touch = 0;
        }
        if (func_02029f58() == 0) {
            UpdateListScrollAnimation_020b7268(menu + 0x64f4, &records[found], data_02060500);
        } else {
            UpdateListScrollAnimation_020b7268(menu + 0x64f4, NULL, 0);
        }
    } else {
        if (*(int *)(menu + 0x66d4) != 0) {
            if (!func_ov001_0207b5f4() || !IsFieldPanelHidden_0207187c() || func_ov001_02064490()) {
                SetEntrySlotsVisible_020b9580(menu + 0x4c, func_ov027_020b90a4(menu + 0x4c, 3), FALSE);
                *(int *)(menu + 0x66d4) = FALSE;
            }
        } else if (func_ov001_0207b5f4() && IsFieldPanelHidden_0207187c() && !func_ov001_02064490()
                   && (func_ov001_02064784() != 0 || !func_ov001_020645c8(0x370b))) {
            SetEntrySlotsVisible_020b9580(menu + 0x4c, func_ov027_020b90a4(menu + 0x4c, 3), TRUE);
            *(int *)(menu + 0x66d4) = TRUE;
        }
        CopySourceBlock_020b9f7c(&block);
        if (func_ov001_0207b6d4()) {
            block.touch = 0;
        }
        if (func_02029f58() == 0) {
            UpdateListScrollAnimation_020b7268(menu + 0x64f4, &block, 0);
        } else {
            UpdateListScrollAnimation_020b7268(menu + 0x64f4, NULL, 0);
        }
    }
    func_ov027_020b7dd4(menu);
    UpdateWidgetRootAndResetList_020b8c80(menu + 0x4c, 0);
    func_ov027_020b9e60((void *)(menu + 0x64c8));
    index = GetAvailableMenuEntryIndex_020b763c(menu + 0x64f4);
    if (*(int *)(menu + 0x66d0) != index) {
        CallVirtualHandlerSlot1_02001574((void *)(menu + 0x669c), 0);
        if (index == -1) {
            func_020016f0((void *)(menu + 0x669c), 4, 0, 2, 10, func_ov027_020ba2a8(func_ov001_0207b748(), 2),
                          GetFieldFont2_020711d4(), 0xe4);
        } else {
            func_020016f0((void *)(menu + 0x669c), 4, 0, 2, 10, func_ov001_0207b6e0(index),
                          GetFieldFont2_020711d4(), 0xe4);
        }
        if (*(u8 *)(menu + 0x64e9) != 0) {
            FlushBufferAndRunCallback_0200153c((void *)(menu + 0x669c));
        } else {
            Text_UploadTileBuffer_02001520((void *)(menu + 0x669c));
        }
        *(int *)(menu + 0x66d0) = index;
    }
    if (*(u8 *)(menu + 0x64e9) != 0) {
        tileTable = func_ov001_0207123c();
        ClearTileTableRowDirty_020b9e30(tileTable, 9);
        ClearTileTableRowDirty_020b9e30(tileTable, 10);
        ClearTileTableRowDirty_020b9e30(tileTable, 11);
        func_ov027_020b9e60(func_ov001_0207123c());
    }
    if (*(u8 *)(menu + 0x64ea) != 0) {
        (*(u8 *)(menu + 0x64ea))--;
        if (*(u8 *)(menu + 0x64ea) == 0) {
            SetSecondaryBrightness_02029ed0(0);
        }
    }
    if (*(int *)(menu + 0x64f0) == 0 && func_ov001_02064784() == 0 && func_ov001_020645c8(0x370b)) {
        func_ov025_020b7658(menu + 0x64f4, 0);
    }
    return 0;
}
