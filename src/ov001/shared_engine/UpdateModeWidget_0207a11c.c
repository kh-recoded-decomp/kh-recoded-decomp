#include "nitro/types.h"

typedef struct ModeState {
    u8 pad0[8];
    int active;
    u8 padC[0x10];
    u8 tween[0x18];
    u32 flag0 : 2;
    u32 freePending : 1;
} ModeState;

extern int *data_ov001_020a04c4;
extern int func_ov001_0207123c(void);
extern int UpdateWidgetLayerDefault_020b9df0(int layer, int index);
extern void func_ov027_020b9e00(int layer, int index);
extern void SampleTweenValue_0205258c(void *tween, s32 *value);
extern void func_ov001_020796f8(ModeState *state, int widget, s32 value);
extern void FreeModeResources_0207942c(ModeState *state);

void UpdateModeWidget_0207a11c(ModeState *state) {
    s32 value;
    int layer = func_ov001_0207123c();
    int widget = UpdateWidgetLayerDefault_020b9df0(layer, 0xb);

    SampleTweenValue_0205258c(state->tween, &value);
    func_ov001_020796f8(state, widget, value);
    if (state->freePending) {
        if (*data_ov001_020a04c4 == 0) {
            state->active = 0;
            return;
        }
        FreeModeResources_0207942c(state);
        *data_ov001_020a04c4 = 0;
    }
    func_ov027_020b9e00(layer, 0xb);
}
