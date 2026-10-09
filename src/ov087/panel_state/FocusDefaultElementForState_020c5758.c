#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[1];
} EntryList;

extern void *func_ov039_020bc1bc(void);
extern void RefreshChoiceMenu_020c4d6c(EntryList *list, BOOL keepFirst);
extern void *FindWidgetById_020b90a4(void *container, int elementId);
extern void SetFocusedWidget_020b96e4(void *container, void *element);
extern void MoveCursorToWidget_020c43c4(EntryList *list, void *element, BOOL narrow, BOOL playSound);

void FocusDefaultElementForState_020c5758(EntryList *list, int stateId)
{
    void *container = func_ov039_020bc1bc();
    u32 selectedId = list->entries[list->cursor].id;
    int elementId;
    void *element;

    RefreshChoiceMenu_020c4d6c(list, TRUE);
    switch (stateId) {
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
        if (selectedId == 6 || selectedId == 3) {
            elementId = 2;
        } else {
            elementId = 3;
        }
        break;
    case 12:
        elementId = 3;
        break;
    case 11:
        switch (selectedId) {
        case 3:
        case 6:
            elementId = 3;
            break;
        case 7:
            elementId = 2;
            break;
        default:
            elementId = 4;
            break;
        }
        break;
    case 13:
        elementId = 2;
        break;
    case 5:
        elementId = selectedId == 6 ? 2 : 3;
        break;
    default:
        elementId = 2;
        break;
    }
    if (stateId != 0x10 && stateId != 0x11) {
        element = FindWidgetById_020b90a4(container, elementId);
        SetFocusedWidget_020b96e4(container, element);
        MoveCursorToWidget_020c43c4(list, element, FALSE, FALSE);
    }
}

