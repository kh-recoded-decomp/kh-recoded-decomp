#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelElement PanelElement;

typedef struct ElementPos {
    fx32 x;
    fx32 y;
} ElementPos;

typedef struct PanelState {
    u8 pad_00[2];
    s8 page;
    u8 pad_03[0x6abd];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov015_0207e960;

extern PanelElement *func_ov027_020b90a4(void *panel, int elementId);
extern void func_ov027_020b96a0(void *panel, PanelElement *element, int mode);
extern void func_ov027_020b9360(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void func_ov027_020b91c8(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void func_ov027_020b96e4(void *panel, PanelElement *element);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void SelectPrevPanelPage_020707f0(void)
{
    ElementPos pos;
    PanelState *state;
    u8 *panel;

    data_ov015_0207e960->page--;
    if (data_ov015_0207e960->page < 0) {
        data_ov015_0207e960->page = 5;
    }
    state = data_ov015_0207e960;
    panel = state->panel;
    func_ov027_020b96a0(panel, func_ov027_020b90a4(panel, 10), state->page);
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9360(panel, func_ov027_020b90a4(panel, 10), &pos, 0);
    pos.x -= 0x19000;
    panel = data_ov015_0207e960->panel;
    func_ov027_020b91c8(panel, func_ov027_020b90a4(panel, 11), &pos, 0);
    panel = data_ov015_0207e960->panel;
    func_ov027_020b96e4(panel, func_ov027_020b90a4(panel, 10));
    PlaySoundEffect_0204d924(2, 1);
}
