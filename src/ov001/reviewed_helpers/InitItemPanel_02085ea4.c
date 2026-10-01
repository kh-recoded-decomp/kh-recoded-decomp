#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Panel Panel;

struct Panel {
    u8 pad_00[0x40];
    VecFx32 position;
    u8 pad_4c[0x58 - 0x4c];
    u32 low : 16;
    s32 itemId : 11;
    u32 high : 5;
    int param;
    u8 pad_60[0x74 - 0x60];
    void *widget;
};

extern void func_ov001_02082714(Panel *panel, int state);
extern void func_ov031_020bc5e0(void *widget);

void InitItemPanel_02085ea4(Panel *panel, const VecFx32 *position, int itemId, int param) {
    func_ov001_02082714(panel, 0);
    panel->position = *position;
    panel->param = param;
    panel->itemId = itemId;
    func_ov031_020bc5e0(panel->widget);
}
