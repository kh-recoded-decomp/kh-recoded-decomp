#include "nitro/types.h"

typedef struct Panel Panel;

struct Panel {
    u8 pad_00[0x6c];
    void (*onClose)(Panel *panel);
};

extern void func_ov001_02082714(Panel *panel, int state);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

int ClosePanelWithSound_020825bc(int unused0, int unused1, int unused2, Panel *panel)
{
    if (panel->onClose != NULL) {
        panel->onClose(panel);
    }
    func_ov001_02082714(panel, 2);
    PlaySoundEffect_0204d924(0, 0x3a);
    return 0;
}
