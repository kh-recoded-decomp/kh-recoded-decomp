#include "nitro/types.h"

typedef struct {
    u8 pad_0000[3];
    s8 blinkTimer;
    u8 pad_0004[0x6abc];
    u8 widgets[4];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern const int data_ov015_0207a19c[];

extern int DispatchContextCommand_02066c78(int command, int a, int b, int c);
extern void func_ov015_0206eba4(void);
extern void *func_ov027_020b90a4(void *widgets, int id);
extern void func_ov027_020b9360(void *widgets, void *widget, int *outPos, int mode);
extern void func_ov027_020b91c8(void *widgets, void *widget, int *pos, int mode);
extern void func_ov027_020b96e4(void *widgets, void *widget);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void StepPanelCursorBlink_020709ec(void) {
    int pos[2];
    void *widgets;

    data_ov015_0207e960->blinkTimer--;
    if (data_ov015_0207e960->blinkTimer < 0) {
        data_ov015_0207e960->blinkTimer = data_ov015_0207a19c[DispatchContextCommand_02066c78(6, 0, 0, 0)] - 1;
    }
    func_ov015_0206eba4();
    widgets = data_ov015_0207e960->widgets;
    func_ov027_020b9360(widgets, func_ov027_020b90a4(widgets, 4), pos, 0);
    pos[0] -= 0x34000;
    pos[1] -= 0x19000;
    widgets = data_ov015_0207e960->widgets;
    func_ov027_020b91c8(widgets, func_ov027_020b90a4(widgets, 0xb), pos, 0);
    widgets = data_ov015_0207e960->widgets;
    func_ov027_020b96e4(widgets, func_ov027_020b90a4(widgets, 4));
    PlaySoundEffect_0204d924(2, 1);
}
