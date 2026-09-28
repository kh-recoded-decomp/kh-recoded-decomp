#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x34];
    u8 layer[0x34];
    s32 unk_68;
    s32 unk_6C;
    u8 pad_070[0x8C];
    s32 state;
    u8 pad_100[0x4];
    s32 mode;
    u8 pad_108[0xC];
    s32 unk_114;
    u8 pad_118[0x8];
    s32 isSuspended;
    s32 unk_124;
    s32 unk_128;
    s32 unk_12C;
    u8 pad_130[0x8];
    s32 unk_138;
    s32 unk_13C;
    s32 unk_140;
    s32 unk_144;
} FieldMenu;

extern s32 data_0205fde4;

extern FieldMenu *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void PXI_Init_02028dac(void);
extern void PXI_Init_02028db8(void);
extern int func_ov001_0207123c(void);
extern u16 *UpdateWidgetLayerDefault_020b9df0(int layers, int layerIndex);
extern void func_ov027_020b9e00(int layers, int layerIndex);
extern void func_ov027_020b9d54(int layers, int layerIndex, int x, int y, int width, int height);
extern void *GetSceneTagTracker_020711b0(void);
extern BOOL func_ov001_02064490(void);
extern void func_ov001_02075ae8(FieldMenu *menu);
extern void func_ov001_020758c4(FieldMenu *menu);
extern void FillBackgroundLayerRect_02001a60(void *info, u16 *dst, int x, int y, u8 palette);
extern void func_ov001_02076cac(FieldMenu *menu);
extern void func_ov001_020769f4(FieldMenu *menu);
extern void func_ov001_02075e10(FieldMenu *menu, void *tracker, s32 mode);
extern void func_ov001_02076ff4(FieldMenu *menu);
extern void func_ov001_02076ebc(FieldMenu *menu, int arg);
extern u16 *func_ov001_020736b4(int layerIndex);
extern u16 *func_ov001_020736d0(int layerIndex);
extern void func_01ff8684(u32 value, void *dst, u32 size);
extern void func_ov001_02075eec(FieldMenu *menu, void *tracker);
extern void func_ov001_020771a8(FieldMenu *menu);

int UpdateFieldMenu_020779f0(void)
{
    FieldMenu *menu = NNSi_FndGetCurrentRootHeap_0202a764();
    u16 *screen = UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(), 0xb);
    void *tracker = GetSceneTagTracker_020711b0();
    int i;

    PXI_Init_02028dac();
    if (menu->isSuspended == 0) {
        if (data_0205fde4 == 0 && menu->unk_138 != 0) {
            if (!func_ov001_02064490()) {
                func_ov001_02075ae8(menu);
            }
            func_ov001_020758c4(menu);
            if (menu->unk_12C != 0) {
                FillBackgroundLayerRect_02001a60(menu->layer, screen, 2, 0x16, menu->unk_128 != 0 ? 9 : 10);
                menu->unk_12C = 0;
            }
        }
        if (menu->state == 0) {
            func_ov001_02076cac(menu);
        } else {
            func_ov001_020769f4(menu);
        }
        if (menu->unk_13C != 0) {
            func_ov001_020769f4(menu);
            func_ov001_02075e10(menu, tracker, menu->mode);
            menu->unk_13C = 0;
        }
        func_ov001_02076ff4(menu);
        if (menu->unk_68 == 0xd || menu->unk_68 != menu->unk_6C) {
            func_ov001_02076ebc(menu, 1);
        }
    }
    if (menu->unk_138 == 0) {
        screen = func_ov001_020736b4(0xb);
        for (i = 0; i < 10; i++) {
            func_01ff8684(0, screen + (i + 0xe) * 32, 0x16);
        }
        func_ov027_020b9e00(func_ov001_0207123c(), 0xb);
    }
    if (menu->unk_124 != 0) {
        func_ov027_020b9d54(func_ov001_0207123c(), 0xb, 0, 0xe, 0xb, 10);
        func_ov001_02075eec(menu, tracker);
        menu->unk_124 = 0;
    }
    if (menu->unk_114 != 0) {
        screen = func_ov001_020736d0(0xb);
        for (i = 5; i < 9; i++) {
            func_01ff8684(0, screen + i * 32, 0x18);
        }
        func_ov027_020b9e00(func_ov001_0207123c(), 0xb);
        menu->unk_114 = 0;
    }
    if (menu->unk_144 >= 0 && menu->unk_140 != 0 && ++menu->unk_144 >= 5) {
        func_ov001_020771a8(menu);
        menu->unk_144 = 5;
    }
    PXI_Init_02028db8();
    return 0;
}
