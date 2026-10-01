#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x34];
    u8 layer[0xc8 - 0x34];
    s32 entryCount;
    u8 pad_0cc[0xec - 0xcc];
    s32 selectedIndex;
    u8 pad_0f0[0x128 - 0xf0];
    s32 highlighted;
} FieldMenu;

extern void *GetSceneTagTracker_020711b0(void);
extern int func_ov001_0207123c(void);
extern u16 *UpdateWidgetLayerDefault_020b9df0(int layer, int index);
extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern void *func_ov001_02075348(FieldMenu *menu, s32 index, s32 slot, s32 flags);
extern void func_ov001_02075b48(FieldMenu *menu, void *entry, u16 *screen, s32 slot, s32 kind, s32 row, s32 palette);
extern void UpdateFieldPromptTag_02075ccc(FieldMenu *menu, void *pool);
extern void FillBackgroundLayerRect_02001a60(void *info, u16 *dst, int x, int y, u8 palette);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void func_ov027_020b822c(void *pool, void *record, int first, s16 second);

void DrawFieldMenuPanel_02075f5c(FieldMenu *menu) {
    void *pool = GetSceneTagTracker_020711b0();
    u16 *screen = UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(), 0xb);
    int row = 0x14;
    int palette;

    if (IsModeSetOrFlag370aClear_0207259c() && menu->entryCount > 0) {
        func_ov001_02075b48(menu, func_ov001_02075348(menu, menu->selectedIndex, 1, 0), screen, 2, 2, row, 1);
        UpdateFieldPromptTag_02075ccc(menu, pool);
        row -= 2;
    }
    if (menu->highlighted != 0) {
        palette = 9;
    } else {
        palette = 10;
    }
    FillBackgroundLayerRect_02001a60(menu->layer, screen, 2, 0x16, palette);
    TagTracker_InvokeCallback_020b8210(pool, FindActiveRecordById_020b8184(pool, 0x21));
    func_ov027_020b822c(pool, FindActiveRecordById_020b8184(pool, 0xe), 0, row);
}
