#include "nitro/types.h"

typedef struct PanelContext {
    u8 pad_0000[0xe4];
    int pendingAction;
    u8 pad_00e8[0x6ac0 - 0xe8];
    u8 entryManager[1];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern int func_ov027_020b90a4(void *manager, int id);
extern void func_ov027_020b95e4(void *manager, int entry);
extern void func_ov027_020b96a0(void *manager, int entry, int mode);

void ResetPanelEntry9_02071ca8(void)
{
    void *manager;

    data_ov015_0207e960->pendingAction = 0;
    manager = data_ov015_0207e960->entryManager;
    func_ov027_020b95e4(manager, func_ov027_020b90a4(manager, 9));
    manager = data_ov015_0207e960->entryManager;
    func_ov027_020b96a0(manager, func_ov027_020b90a4(manager, 9), 0);
}
