#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[10];
    u8 pad_b68[0x8];
    PanelStackEntry stack[6];
    int depth;
    u8 pad_ba4[0x14];
    int pendingSlot;
} PanelScene;

typedef struct {
    u8 pad_00[0xc];
    int id;
} Widget;

extern BOOL IsSessionFlagClear_020c4260(PanelScene *scene, int index);
extern void PushPanelState_020c61b0(PanelScene *scene, int stateId);

BOOL SelectChoiceWidget_020c44a4(PanelScene *scene, Widget *widget)
{
    int state = scene->stack[scene->depth].stateId;
    int slot;

    switch (state) {
    case 1:
    case 2:
    case 3:
        switch (scene->entries[scene->cursor].id) {
        case 3:
            switch (widget->id) {
            case 2:
                slot = 2;
                break;
            case 3:
                slot = 0;
                break;
            default:
                return FALSE;
            }
            break;
        case 6:
            switch (widget->id) {
            case 2:
                slot = 0;
                break;
            case 3:
                slot = 1;
                break;
            default:
                return FALSE;
            }
            break;
        case 7:
            if (state == 1) {
                if (widget->id == 2) {
                    slot = 0;
                } else if (widget->id == 3) {
                    slot = 1;
                } else {
                    return FALSE;
                }
            } else {
                if (widget->id == 3) {
                    slot = 0;
                } else if (widget->id == 4) {
                    slot = 1;
                } else {
                    return FALSE;
                }
            }
            break;
        default:
            switch (widget->id) {
            case 2:
                slot = 2;
                break;
            case 3:
                slot = 0;
                break;
            case 4:
                slot = 1;
                break;
            default:
                return FALSE;
            }
            break;
        }
        break;
    default:
        return FALSE;
    }
    if (!IsSessionFlagClear_020c4260(scene, slot)) {
        return FALSE;
    }
    scene->pendingSlot = slot;
    PushPanelState_020c61b0(scene, 0x10);
    return TRUE;
}
