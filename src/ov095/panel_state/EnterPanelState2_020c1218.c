#include "nitro/types.h"

typedef struct {
    u8 pad[0x11104];
    int state;
} PanelWork;

extern void SetPanelMode_020c11f0(int mode, PanelWork *work);

void EnterPanelState2_020c1218(PanelWork *work) {
    work->state = 2;
    SetPanelMode_020c11f0(2, work);
}
