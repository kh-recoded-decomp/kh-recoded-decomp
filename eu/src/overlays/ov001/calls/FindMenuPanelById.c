#pragma opt_propagation off
#include "nitro/types.h"

typedef struct MenuPanelDefinition {
    u8 id;
} MenuPanelDefinition;

typedef struct MenuPanel {
    u8 pad_00[0x1c];
    const MenuPanelDefinition *definition;
    u8 pad_20[4];
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
    u8 pad_04[9];
    s8 selected;
    u8 pad_0e[6];
    MenuPanel *panels;
} MenuScene;

extern MenuScene *data_ov001_020a048c;

MenuPanel *FindMenuPanelById(int panelId)
{
    MenuScene *scene = data_ov001_020a048c;
    MenuItem *item;
    int index;
    int panelCount;

    item = scene->table->items[scene->selected];
    index = 0;
    panelCount = item->panelCount;

    if (panelCount > 0) {
        do {
            MenuPanel *panel = &scene->panels[index];

            if (panelId == panel->definition->id) {
                return panel;
            }
            index++;
        } while (index < panelCount);
    }
    return NULL;
}
