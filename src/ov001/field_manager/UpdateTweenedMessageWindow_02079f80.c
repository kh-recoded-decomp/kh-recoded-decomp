#include "nitro/types.h"

typedef struct Tween Tween;

typedef struct MessageWindow {
    int layer;
    u8 pad_04[4];
    int state;
    u8 pad_0c[0x10];
    u8 tween[0x18];
    u32 unk34_0 : 2;
    u32 opening : 1;
    u32 unk34_3 : 29;
    u8 pad_38[0x10];
    s32 closeTimer;
    u8 pad_4c[0x38];
    u32 tickLo;
    u32 tickHi;
} MessageWindow;

extern s32 *data_ov001_020a04c4;
extern int func_ov001_0207123c(void);
extern int UpdateWidgetLayerDefault_020b9df0(int widgets, int layer);
extern void MarkTileTableRowDirty_020b9e00(int widgets, int layer);
extern void SampleTweenValue_0205258c(Tween *tween, s32 *out);
extern void DrawScaledWindowFrame_020796f8(MessageWindow *window, int target, int percent);
extern void func_ov001_020794c8(MessageWindow *window);
extern void func_ov001_02079e2c(MessageWindow *window);
extern u64 OS_GetTick_02003fd4(void);

void UpdateTweenedMessageWindow_02079f80(MessageWindow *window)
{
    int widgets = func_ov001_0207123c();
    int target = UpdateWidgetLayerDefault_020b9df0(widgets, 11);
    s32 *mode = data_ov001_020a04c4;
    s32 percent;

    SampleTweenValue_0205258c((Tween *)window->tween, &percent);
    DrawScaledWindowFrame_020796f8(window, target, percent);
    if (window->opening) {
        func_ov001_020794c8(window);
        if ((window->closeTimer != 0x7fffffff && *mode == 8) || *mode == 9) {
            func_ov001_02079e2c(window);
        }
        *(u64 *)&window->tickLo = OS_GetTick_02003fd4();
        window->state = 4;
    }
    MarkTileTableRowDirty_020b9e00(widgets, 11);
}
