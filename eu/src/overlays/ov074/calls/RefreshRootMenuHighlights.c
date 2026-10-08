#include "nitro/types.h"

typedef struct ElementPair {
    int icon;
    int text;
} ElementPair;

typedef struct RootMenu {
    u8 cursor;
    u8 entryCount;
    u8 state;
    u8 mode;
    u8 optionCursor;
    u8 pad_05[0x57c - 0x05];
    void *objManager;
    ElementPair itemElements[8];
    int cursorElement;
    int headerElement;
    int frameElement;
    ElementPair optionElements[2];
} RootMenu;

extern void SetEntrySlotsVisible(void *manager, int element, BOOL visible);
extern int *GetWidgetPosition(void *manager, int element);
extern void func_ov027_020b91e8(void *manager, int element, int *position, int flags);

void RefreshRootMenuHighlights(const RootMenu *menu)
{
    BOOL inOptions;
    BOOL inList;
    void *manager;
    int i;
    int element;

    manager = menu->objManager;
    inList = menu->mode == 0;
    inOptions = menu->mode == 1;

    for (i = 0; i < menu->entryCount; i++) {
        SetEntrySlotsVisible(manager, menu->itemElements[i].icon, inList && i != menu->cursor);
        SetEntrySlotsVisible(manager, menu->itemElements[i].text, inList && i == menu->cursor);
    }
    for (i = 0; i < 2; i++) {
        SetEntrySlotsVisible(manager, menu->optionElements[i].icon, inOptions && i != menu->optionCursor);
        SetEntrySlotsVisible(manager, menu->optionElements[i].text, inOptions && i == menu->optionCursor);
    }
    if (inList) {
        element = menu->itemElements[menu->cursor].text;
    } else {
        element = menu->optionElements[menu->optionCursor].text;
    }
    func_ov027_020b91e8(manager, menu->cursorElement, GetWidgetPosition(manager, element), 0);
}
