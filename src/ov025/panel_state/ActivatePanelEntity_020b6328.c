#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0x64f0];
    int active;
    u8 entity[0xa0];
} PanelState;

extern PanelState *data_ov025_020b7760;
extern void func_ov025_020b766c(void *entity, int mode);

void ActivatePanelEntity_020b6328(void) {
    data_ov025_020b7760->active = 1;
    func_ov025_020b766c(data_ov025_020b7760->entity, 3);
}
