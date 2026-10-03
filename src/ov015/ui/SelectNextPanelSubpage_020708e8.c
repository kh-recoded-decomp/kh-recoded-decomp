#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelElement PanelElement;

typedef struct ElementPos {
    fx32 x;
    fx32 y;
} ElementPos;

typedef struct PanelState {
    u8 pad_00[3];
    s8 subpage;
    u8 pad_04[0x6abc];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov015_0207e960;
extern int data_ov015_0207a19c[];

extern u32 DispatchContextCommand_02066c78(u32 command, u32 value, u32 extra, void *buffer);
extern void func_ov015_0206eba4(void);
extern PanelElement *func_ov027_020b90a4(void *panel, int elementId);
extern void func_ov027_020b9360(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void func_ov027_020b91c8(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void func_ov027_020b96e4(void *panel, PanelElement *element);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void SelectNextPanelSubpage_020708e8(void)
{
    ElementPos pos;
    PanelState *state;
    u8 *panel;

    data_ov015_0207e960->subpage++;
    state = data_ov015_0207e960;
    if (state->subpage >= data_ov015_0207a19c[DispatchContextCommand_02066c78(6, 0, 0, NULL)]) {
        state->subpage = 0;
    }
    func_ov015_0206eba4();
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9360(panel, func_ov027_020b90a4(panel, 4), &pos, 0);
    pos.x -= 0x34000;
    pos.y -= 0x19000;
    panel = data_ov015_0207e960->panel;
    func_ov027_020b91c8(panel, func_ov027_020b90a4(panel, 11), &pos, 0);
    panel = data_ov015_0207e960->panel;
    func_ov027_020b96e4(panel, func_ov027_020b90a4(panel, 4));
    PlaySoundEffect_0204d924(2, 1);
}
