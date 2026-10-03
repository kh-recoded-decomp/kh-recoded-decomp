#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    u16 flags;
    u8 pad_2A[2];
    s32 unk_2C;
} FieldEntry;

typedef struct {
    u8 pad_000[0x34];
    u8 layer[0x34];
    s32 unk_68;
    u8 pad_06C[0x5C];
    s32 unk_C8;
    u8 pad_0CC[0x20];
    s32 entryIndex;
    s32 groupIndex;
    u8 pad_0F4[0x8];
    s32 state;
    u8 pad_100[0x4];
    s32 mode;
    s32 idleCount;
    u8 pad_10C[0x10];
    void *cursorRecord;
    u8 pad_120[0x8];
    s32 unk_128;
    u8 pad_12C[0x8];
    s32 unk_134;
} FieldMenu;

extern int func_ov001_0207123c(void);
extern u16 *UpdateWidgetLayerDefault_020b9df0(int layers, int layerIndex);
extern void *GetSceneTagTracker_020711b0(void);
extern FieldEntry *func_ov001_02075348(FieldMenu *menu, s32 index, s32 slot, s32 *outValue);
extern void func_ov001_02075b48(FieldMenu *menu, FieldEntry *entry, u16 *screen, s32 slot, s32 kind, s32 row, s32 palette);
extern void func_ov027_020b822c(void *tracker, void *record, u16 x, u16 y);
extern void func_ov001_02075db8(FieldMenu *menu);
extern void func_ov001_02075ccc(FieldMenu *menu, void *tracker);
extern BOOL func_ov001_020728a4(void);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void FillBackgroundLayerRect_02001a60(void *info, u16 *dst, int x, int y, u8 palette);

void DrawFieldMenuSlotsAlt_0207639c(FieldMenu *menu)
{
    u16 *screen = UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(), 0xb);
    void *tracker = GetSceneTagTracker_020711b0();
    s32 first = -(menu->unk_C8 >= 3);
    s32 i;
    FieldEntry *entry;
    s32 slotIndex;
    void *record;

    for (i = first; i < 2; i++) {
        entry = func_ov001_02075348(menu, menu->groupIndex, i + 1, &slotIndex);
        func_ov001_02075b48(menu, entry, screen, i + 1, 1, i * 2 + 0x13, 9);
    }
    if (first == 0) {
        switch (menu->mode) {
        case 0:
            entry = func_ov001_02075348(menu, 2, 1, NULL);
            break;
        case 1:
            entry = func_ov001_02075348(menu, 0xe, 1, NULL);
            break;
        case 2:
            entry = func_ov001_02075348(menu, 2, 1, NULL);
            break;
        }
        func_ov001_02075b48(menu, entry, screen, 0, 1, 0x10, 9);
        func_ov027_020b822c(tracker, menu->cursorRecord, 0, 0x10);
    } else {
        func_ov027_020b822c(tracker, menu->cursorRecord, 0, 0x11);
    }
    func_ov027_020b822c(tracker, menu->cursorRecord, 0, 0x13);
    func_ov027_020b822c(tracker, menu->cursorRecord, 0, 0x15);
    if (menu->unk_68 != 10) {
        if (func_ov001_020728a4()) {
            TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, menu->mode == 1 ? 0xd : 0xe));
        } else {
            TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0xc));
        }
    } else {
        InvokeCallback40_020b8268(tracker, FindActiveRecordById_020b8184(tracker, 0xc));
    }
    if (menu->unk_68 != 10) {
        record = FindActiveRecordById_020b8184(tracker, 0x21);
    } else {
        record = FindActiveRecordById_020b8184(tracker, 0x24);
    }
    TagTracker_InvokeCallback_020b8210(tracker, record);
    FillBackgroundLayerRect_02001a60(menu->layer, screen, 2, 0x16, menu->unk_128 != 0 ? 9 : 10);
    menu->state = 4;
    menu->idleCount = 0;
}
