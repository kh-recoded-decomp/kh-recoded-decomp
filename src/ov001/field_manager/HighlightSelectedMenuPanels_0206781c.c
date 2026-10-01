#include "nitro/types.h"

typedef struct PanelDef {
    u8 pad_00[3];
    u8 itemNumber;
} PanelDef;

typedef struct MenuPanel {
    u8 pad_00[0x1c];
    PanelDef *def;
    u8 pad_20[2];
    u16 flags;
} MenuPanel;

typedef struct MenuItem {
    u8 kind;
    u8 panelCount;
} MenuItem;

typedef struct MenuItemTable {
    u8 pad_00[8];
    MenuItem *items[1];
} MenuItemTable;

typedef struct MenuScene {
    MenuItemTable *table;
    u8 pad_04[8];
    s8 mode;
    s8 selected;
    u8 pad_0E;
    u8 flags;
    u8 pad_10[4];
    MenuPanel *panels;
} MenuScene;

extern MenuScene *data_ov001_020a046c;
extern void SetPanelItemHighlight_0207b19c(int index, BOOL highlighted);
extern void OpenFieldMenuForMode_0207214c(u32 menuId, u32 option);

void HighlightSelectedMenuPanels_0206781c(void)
{
    MenuScene *scene = data_ov001_020a046c;
    MenuItem *item;
    int i = 0;

    scene->flags |= 1;
    item = data_ov001_020a046c->table->items[scene->selected];
    for (; i < item->panelCount; i++) {
        MenuPanel *panel = &scene->panels[i];

        SetPanelItemHighlight_0207b19c(panel->def->itemNumber - 1, panel->flags & 2);
    }
    OpenFieldMenuForMode_0207214c(scene->mode, item->kind);
}
