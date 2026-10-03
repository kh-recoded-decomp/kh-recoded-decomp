#include "nitro/types.h"

typedef struct ItemDef {
    u32 handle;
    s32 kind;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u8 pad_06[2];
    ItemDef *def;
} ItemStock;

typedef struct MenuPanel {
    u8 pad_00000[0x3c18];
    ItemStock *entries[(0x4d84 - 0x3c18) / 4];
    s16 entryCount;
    s16 cursorIndex;
    u8 pad_04D88[0x7f94 - 0x4d88];
    u32 currentHandle;
    s16 currentRecord;
    u8 pad_07F9A[0x11e24 - 0x7f9a];
    u8 customCategoryCount;
    u8 pad_11E25[3];
    u32 customCategories[1];
} MenuPanel;

extern BOOL IsItemSlotAvailable_020c9d20(ItemStock *stock, u8 categoryCount, const u32 *categories);
extern void MenuPanel_Finish_020c9c5c(MenuPanel *panel, BOOL confirmed);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

int MenuPanel_ConfirmSelection_020ca988(MenuPanel *panel)
{
    if (panel->cursorIndex < panel->entryCount) {
        BOOL current;
        ItemDef *def;
        ItemStock *stock;
        BOOL accept;

        stock = panel->entries[panel->cursorIndex];
        accept = FALSE;
        current = FALSE;
        def = stock->def;

        if (def->handle == panel->currentHandle && stock->recordIndex == panel->currentRecord) {
            current = TRUE;
        }
        if (current) {
            switch (def->kind) {
            case 0:
            case 2:
            case 3:
                accept = TRUE;
                break;
            }
        }
        if (IsItemSlotAvailable_020c9d20(stock, panel->customCategoryCount, panel->customCategories)) {
            accept = TRUE;
        }
        if (accept) {
            MenuPanel_Finish_020c9c5c(panel, TRUE);
            return 2;
        }
    }
    PlaySoundEffect_0204d924(1, 4);
    return 1;
}
