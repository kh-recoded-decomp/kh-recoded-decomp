#include "nitro/types.h"

typedef struct PanelContext {
    u8 pad_0000[0xbb];
    u8 selectedOption;
    u8 pad_00bc[0x6ac0 - 0xbc];
    u8 entryManager[1];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern int func_ov027_020b90a4(void *manager, int id);
extern void func_ov027_020b96e4(void *manager, int entry);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void SelectPanelOptionB_020728f8(void)
{
    data_ov015_0207e960->selectedOption = 2;
    func_ov027_020b96e4(data_ov015_0207e960->entryManager, func_ov027_020b90a4(data_ov015_0207e960->entryManager, 8));
    PlaySoundEffect_0204d924(2, 1);
}
