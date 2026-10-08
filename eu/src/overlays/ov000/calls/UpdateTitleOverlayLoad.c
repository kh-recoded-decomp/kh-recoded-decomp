#include "nitro/types.h"

typedef struct TitlePanel {
    u8 pad_00[0x6684];
    s32 overlayLoaded;
    u8 pad_6688[0x44];
    void *overlayTask;
    u8 pad_66d0[8];
    s32 skipFade;
} TitlePanel;

extern u8 UpdateMenuTouchSelect[];

extern int func_ov003_02064744(void);
extern BOOL IsSoundStreamActive(int handleIndex);
extern void *func_0202a45c(void *descriptor, void *userData);
extern void SetPanelState(TitlePanel *panel, s32 state, u32 param1, u32 param2);

int UpdateTitleOverlayLoad(TitlePanel *panel)
{
    int result = -1;

    if (panel->overlayLoaded != 0) {
        if (func_ov003_02064744() != 0) {
            if (panel->skipFade != 0) {
                SetPanelState(panel, 1, 0, 0);
                result = -2;
            } else {
                SetPanelState(panel, 1, 0, 30);
                result = 6;
            }
        }
    } else if (!IsSoundStreamActive(0)) {
        panel->overlayTask = func_0202a45c(UpdateMenuTouchSelect, (void *)result);
        panel->overlayLoaded = 1;
    }
    return result;
}
