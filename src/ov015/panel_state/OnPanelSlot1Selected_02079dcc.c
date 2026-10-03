#include "nitro/types.h"

typedef struct PanelEntry {
    u8 pad_00[0x14];
    int animSlot;
} PanelEntry;

typedef struct PanelWork {
    u8 pad_0000[0x14];
    int mode;
    u8 pad_0018[0x148];
    u8 panel[0x647c];
    void *animOwner;
} PanelWork;

extern PanelWork *data_ov015_020812e0;

extern PanelEntry *func_ov027_020b90a4(void *panel, int slot);
extern void func_ov027_020b9874(void *panel, int value);
extern void func_ov027_020b984c(void *panel, int value);
extern void SetSlotAnimSequence_0204f24c(void *owner, int slot, int sequence);
extern void func_ov015_020779a4(int a, int b);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void OnPanelSlot1Selected_02079dcc(void)
{
    PanelEntry *entry = func_ov027_020b90a4(data_ov015_020812e0->panel, 1);

    if (entry != NULL) {
        SetSlotAnimSequence_0204f24c(data_ov015_020812e0->animOwner, entry->animSlot, 1);
    }
    func_ov027_020b9874(data_ov015_020812e0->panel, 0);
    func_ov027_020b984c(data_ov015_020812e0->panel, 0);
    data_ov015_020812e0->mode = 6;
    func_ov015_020779a4(0x24, 0x1f);
    PlaySoundEffect_0204d924(2, 1);
}
