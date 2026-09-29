#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    u16 flags;
    u16 count;
} GaugeEntry;

typedef struct {
    u8 pad_000[0x34];
    u8 layer[0x34];
    s32 unk_68;
    u8 pad_06C[0x5C];
    s32 unk_C8;
    u8 pad_0CC[0x20];
    s32 unk_EC;
    u8 pad_0F0[0x14];
    s32 unk_104;
    u8 pad_108[0x14];
    s32 unk_11C;
    u8 pad_120[8];
    s32 unk_128;
} FieldMenu;

extern int func_ov001_0207123c(void);
extern u16 *UpdateWidgetLayerDefault_020b9df0(int layers, int layerIndex);
extern void *GetSceneTagTracker_020711b0(void);
extern GaugeEntry *func_ov001_02075348(FieldMenu *menu, s32 group, s32 slot, s32 *outIndex);
extern void func_ov001_02075b48(FieldMenu *menu, GaugeEntry *entry, u16 *screen, s32 slot, s32 mode, s32 row,
                                s32 palette);
extern void func_ov001_02075ccc(FieldMenu *menu, void *tracker);
extern void func_ov027_020b822c(void *tracker, s32 handle, u16 arg2, u16 arg3);
extern void *FindActiveRecordById_020b8184(void *tracker, u16 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *record);
extern void InvokeCallback40_020b8268(void *tracker, void *record);
extern BOOL func_ov001_020728a4(void);
extern void FillBackgroundLayerRect_02001a60(void *info, u16 *dst, int x, int y, u8 palette);

void DrawPartyGaugeFrames_02076008(FieldMenu *menu)
{
    u16 *screen;
    void *tracker;
    GaugeEntry *entry;
    s32 index;
    s32 mode;
    s32 slot;

    screen = UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(), 11);
    tracker = GetSceneTagTracker_020711b0();
    for (index = -1; index < 2; index++) {
        if ((menu->unk_C8 == 2 && index == -1) || (menu->unk_C8 == 1 && index != 0)) {
            switch (menu->unk_104) {
            case 0:
                slot = 2;
                entry = func_ov001_02075348(menu, slot, 1, NULL);
                break;
            case 1:
                entry = func_ov001_02075348(menu, 14, 1, NULL);
                break;
            case 2:
                entry = func_ov001_02075348(menu, 2, 1, NULL);
                break;
            }
        } else {
            entry = func_ov001_02075348(menu, menu->unk_EC, index + 1, &slot);
        }
        mode = (index == 0 && (entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) ? 2 : 1;
        func_ov001_02075b48(menu, entry, screen, index + 1, mode, index * 2 + 18, mode == 2 ? 1 : 9);
    }
    entry = func_ov001_02075348(menu, menu->unk_EC, 1, NULL);
    if ((entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) {
        func_ov001_02075ccc(menu, tracker);
    } else {
        func_ov027_020b822c(tracker, menu->unk_11C, 0, 0x12);
    }
    if (menu->unk_68 != 10) {
        TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x21));
    } else {
        TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x24));
    }
    func_ov027_020b822c(tracker, menu->unk_11C, 0, 0x10);
    func_ov027_020b822c(tracker, menu->unk_11C, 0, 0x14);
    if (menu->unk_68 != 10) {
        if (func_ov001_020728a4()) {
            TagTracker_InvokeCallback_020b8210(tracker,
                                               FindActiveRecordById_020b8184(tracker, menu->unk_104 == 1 ? 0xD : 0xE));
        } else {
            TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0xC));
        }
    } else {
        InvokeCallback40_020b8268(tracker, FindActiveRecordById_020b8184(tracker, 0xC));
    }
    FillBackgroundLayerRect_02001a60(menu->layer, screen, 2, 22, menu->unk_128 != 0 ? 9 : 10);
}
