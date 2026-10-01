#include "nitro/types.h"

typedef struct PanelOwner {
    u8 pad_000[0x494];
    int scrollSpeed;
} PanelOwner;

typedef struct Panel Panel;

struct Panel {
    u8 pad_00[8];
    PanelOwner *owner;
    u8 pad_0C[0x5c];
    void (*update)(Panel *panel);
    void (*draw)(Panel *panel);
    int state;
};

extern void func_ov001_02085edc(Panel *panel);
extern void func_ov001_02085ee0(Panel *panel);

void SetupPanelHandlers_02085f18(Panel *panel)
{
    panel->owner->scrollSpeed = 0x1800;
    panel->update = func_ov001_02085edc;
    panel->draw = func_ov001_02085ee0;
    panel->state = 0;
}
