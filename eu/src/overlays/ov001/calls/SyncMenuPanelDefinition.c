#include "nitro/types.h"

typedef struct MenuPanelDefinition {
    u8 id;
    u8 value;
    u8 level;
    u8 pad_03;
    u16 flags;
    u8 pad_06[2];
} MenuPanelDefinition;

typedef struct MenuPanel {
    u8 pad_00[0x1c];
    const MenuPanelDefinition *definition;
    u8 value;
    u8 level;
    u16 flags;
} MenuPanel;

typedef struct MenuScene {
    u8 pad_00[0x14];
    MenuPanel *panels;
} MenuScene;

extern MenuScene *data_ov001_020a048c;

void SyncMenuPanelDefinition(const MenuPanelDefinition *definition, int index)
{
    MenuPanel *panel = &data_ov001_020a048c->panels[index];

    panel->value = definition->value;
    panel->level = definition->level;
    panel->flags = definition->flags;
    panel->definition = definition;
}
