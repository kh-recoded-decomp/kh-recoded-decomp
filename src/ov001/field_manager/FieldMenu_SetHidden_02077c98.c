#include "nitro/types.h"

typedef struct FieldMenu {
    u8 pad_000[0x104];
    s32 mode;
    u8 pad_108[0x140 - 0x108];
    int hidden;
} FieldMenu;

typedef struct FieldMenuHandle {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;
extern void *GetSceneTagTracker_020711b0(void);
extern void func_ov001_02075e10(FieldMenu *menu, void *tracker, s32 mode);
extern void *func_ov027_020b8390(void *tracker, int id);
extern void func_ov027_020b83e8(void *tracker, void *entry, u32 flag);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);

void FieldMenu_SetHidden_02077c98(int hidden)
{
    void *tracker = GetSceneTagTracker_020711b0();
    FieldMenu *menu = data_ov001_020a04b0.menu;

    if (menu->hidden == hidden) {
        return;
    }
    menu->hidden = hidden;
    if (hidden != 0) {
        func_ov001_02075e10(menu, tracker, menu->mode);
        return;
    }
    func_ov027_020b83e8(tracker, func_ov027_020b8390(tracker, 10), 0);
    func_ov027_020b83e8(tracker, func_ov027_020b8390(tracker, 11), 0);
    func_ov027_020b83e8(tracker, func_ov027_020b8390(tracker, 12), 0);
    func_ov027_020b83e8(tracker, func_ov027_020b8390(tracker, 17), 0);
    func_ov027_020b83e8(tracker, func_ov027_020b8390(tracker, 18), 0);
    InvokeCallback40_020b8268(tracker, FindActiveRecordById_020b8184(tracker, 0x5d));
    InvokeCallback40_020b8268(tracker, FindActiveRecordById_020b8184(tracker, 0x5b));
    InvokeCallback40_020b8268(tracker, FindActiveRecordById_020b8184(tracker, 0x5c));
    InvokeCallback40_020b8268(tracker, FindActiveRecordById_020b8184(tracker, 0x55));
}
