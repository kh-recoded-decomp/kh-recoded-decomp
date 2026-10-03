#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_0000[0x14];
    int mode;
    u8 pad_0018[0x148];
    u8 panel[1];
} PanelWork;

extern PanelWork *data_ov015_020812e0;

extern void *func_ov027_020b90a4(void *panel, int slot);
extern void func_ov027_020b96e4(void *panel, void *entry);
extern void func_ov027_020b9874(void *panel, int value);
extern void func_ov027_020b984c(void *panel, int value);
extern void func_ov015_020779a4(int a, int b);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void OnPanelSlot16Selected_02079e5c(void)
{
    func_ov027_020b96e4(data_ov015_020812e0->panel, func_ov027_020b90a4(data_ov015_020812e0->panel, 0x10));
    func_ov027_020b9874(data_ov015_020812e0->panel, 0);
    func_ov027_020b984c(data_ov015_020812e0->panel, 0);
    data_ov015_020812e0->mode = 4;
    func_ov015_020779a4(0x24, 0x22);
    PlaySoundEffect_0204d924(2, 1);
}
