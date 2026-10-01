#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x667c];
    int number;
    BOOL useAltMode;
    BOOL requestSent;
    u8 pad_6688[0x66a4 - 0x6688];
    BOOL (*isRequestDone)(void);
} Panel;

extern BOOL IsSoundStreamActive_0204ded4(int handleIndex);
extern void SetPanelState_02061db0(Panel *panel, s32 state, u32 param1, u32 param2);
extern void SubmitNumberedPanelRequest_02061f54(Panel *panel, BOOL useAltMode, int number);

s32 UpdatePanelRequest_02062d60(Panel *panel)
{
    s32 result = -1;

    if (panel->requestSent) {
        if (panel->isRequestDone()) {
            if (panel->useAltMode) {
                SetPanelState_02061db0(panel, 1, 0, 0);
                result = 10;
            } else {
                SetPanelState_02061db0(panel, 1, 0, 0x10);
                result = 6;
            }
        }
    } else if (!IsSoundStreamActive_0204ded4(0)) {
        SubmitNumberedPanelRequest_02061f54(panel, panel->useAltMode, panel->number);
        panel->requestSent = TRUE;
    }
    return result;
}
