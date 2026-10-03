#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CellSize {
    fx32 width;
    fx32 height;
} CellSize;

typedef struct CellSprite {
    s16 x;
    s16 y;
    u16 width;
    u16 height;
    u32 flags;
    u8 pad_0c[0x10 - 0xc];
    CellSize size;
    u8 pad_18[0x24 - 0x18];
    u8 alpha;
    u8 index;
    u8 pad_26[0x30 - 0x26];
} CellSprite;

typedef struct GaugePanel {
    CellSprite cells[3];
    u8 blink[0x1b0 - 0x90];
    u8 current;
    u8 maximum;
    u8 pad_1b2[0x1c0 - 0x1b2];
    int timer;
} GaugePanel;

typedef struct PanelOwner {
    u8 pad_000[0x934];
    s32 mode : 8;
    s32 modeRest : 24;
} PanelOwner;

extern int func_ov001_02063a4c(void);
extern void func_ov059_020cf6cc(void *blink);
extern void NNS_FndInitListWithOffset0_0206ad28(CellSprite *cell);
extern void SetPendingSlotFlag_0207d4d0(int flag);

void GaugePanel_Update_020cfd1c(GaugePanel *panel, PanelOwner *owner) {
    int last;
    CellSize size;
    int i;

    if (func_ov001_02063a4c() != 4) {
        return;
    }
    func_ov059_020cf6cc(panel->blink);
    if (owner->mode == 2) {
        last = 1;
        panel->cells[1].size = panel->cells[0].size;
    } else {
        last = 0;
        size = panel->cells[0].size;
        size.width -= 0x14000;
        for (i = 0; i < 2; i++) {
            panel->cells[2].index = i;
            if (i == 1) {
                size.width += 0x28000;
            }
            panel->cells[2].size = size;
            NNS_FndInitListWithOffset0_0206ad28(&panel->cells[2]);
        }
    }
    NNS_FndInitListWithOffset0_0206ad28(&panel->cells[last]);
    if (owner->mode == 2 && panel->current == panel->maximum) {
        if (panel->timer % 0x8000 < 0x5000) {
            SetPendingSlotFlag_0207d4d0(0);
        }
        panel->timer += 0x1000;
    }
}
