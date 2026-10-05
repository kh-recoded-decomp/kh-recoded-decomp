#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6684];
    s32 overlayLoaded;
    u8 pad_6688[0x66cc - 0x6688];
    void *overlayTask;
    u8 pad_66d0[0x66d8 - 0x66d0];
    s32 skipFade;
} Panel;

extern u8 TitleTaskDescriptor_020650e0[];

extern int func_ov003_02064744(void);
extern BOOL IsSoundStreamActive_0204ded4(int handleIndex);
extern void *func_0202a448(void *descriptor, void *userData);
extern void SetPanelState_02061db0(Panel *panel, s32 state, u32 param1, u32 param2);

int UpdateTitleOverlayLoad_02062e64(Panel *panel)
{
    int result = -1;

    if (panel->overlayLoaded != 0) {
        if (func_ov003_02064744() != 0) {
            if (panel->skipFade != 0) {
                SetPanelState_02061db0(panel, 1, 0, 0);
                result = -2;
            } else {
                SetPanelState_02061db0(panel, 1, 0, 30);
                result = 6;
            }
        }
    } else if (!IsSoundStreamActive_0204ded4(0)) {
        panel->overlayTask = func_0202a448(TitleTaskDescriptor_020650e0, (void *)result);
        panel->overlayLoaded = 1;
    }
    return result;
}
