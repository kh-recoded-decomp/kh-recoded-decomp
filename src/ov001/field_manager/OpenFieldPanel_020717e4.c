#include "nitro/types.h"

typedef struct {
    s32 mode;
    s32 duration;
    s32 startValue;
    s32 endValue;
    u8 pad_10[0xC];
} PanelTween;

typedef struct {
    u8 pad_000[0x47C];
    s32 panelState;
    u32 isSliding : 1;
    u32 unk_480_1 : 31;
    u8 pad_484[0x158];
    PanelTween slideTween;
    u8 pad_5F8[0xC];
    s32 slideOffset;
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;
extern BOOL g_currentActive_0205fde4;

extern void func_02052514(PanelTween *tween, int mode, int startValue, int endValue, int duration);
extern void func_0205255c(PanelTween *tween);
extern void func_ov001_02077b90(int enable, int arg1);
extern void func_ov001_020701a8(FieldManager *manager);
extern void func_ov001_0206fcc8(FieldManager *manager);

BOOL OpenFieldPanel_020717e4(void)
{
    FieldManager *manager = data_ov001_020a04a4.manager;

    if (manager->panelState != 0) {
        return FALSE;
    }
    if (g_currentActive_0205fde4 != FALSE) {
        return FALSE;
    }
    func_02052514(&manager->slideTween, 2, 0, 0x60000, 100);
    func_0205255c(&manager->slideTween);
    manager->isSliding = TRUE;
    manager->slideOffset = 0;
    func_ov001_02077b90(1, 1);
    manager->panelState = 1;
    func_ov001_020701a8(manager);
    func_ov001_0206fcc8(manager);
    return TRUE;
}
