#include "nitro/types.h"

typedef struct {
    u8 pad_00[3];
    u8 mode;
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void SetPanelModeWithSound_020746d0(void) {
    data_ov013_02074ce0->mode = 1;
    PlaySoundEffect_0204d924(2, 1);
}
