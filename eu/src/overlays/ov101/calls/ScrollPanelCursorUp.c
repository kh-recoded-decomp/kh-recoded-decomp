#include "nitro/types.h"

typedef struct {
    s32 recordIndex;
    s32 x;
    s32 y;
    u8 pad_0C[0x10];
} SlotEntry;

typedef struct {
    s32 listId;
    s32 itemCount;
    s32 visibleRows;
    s32 entryIndex;
    u8 pad_10[0x1C];
    s32 scroll;
    s32 cursor;
    u8 pad_34[0x18];
} ScrollPanel;

typedef struct {
    u8 pad_0000[0x184];
    u8 slotLists[2][0x6434];
    SlotEntry primaryEntries[12];
    SlotEntry secondaryEntries[12];
    u8 pad_CC84[0xE0];
    ScrollPanel panels[2];
} Ov101State;

extern u16 data_02060500;
extern void func_ov101_020c00b8(int listIndex, int entryIndex, int x, int y, Ov101State *state);
extern void func_ov101_020c082c(int listId, Ov101State *state);

BOOL ScrollPanelCursorUp(int panelIndex, Ov101State *state)
{
    ScrollPanel *panel = &state->panels[panelIndex];
    SlotEntry *entry;
    int cursor;
    int entryIndex;

    if (panel->entryIndex < 0) {
        panel->cursor = 0;
    }
    cursor = panel->cursor;
    if (panel->scroll + cursor > 0) {
        if (cursor == 0) {
            panel->scroll--;
        } else {
            panel->cursor = cursor - 1;
            entryIndex = panel->entryIndex;
            if (entryIndex >= 0) {
                if (panelIndex == 0) {
                    entry = &state->primaryEntries[entryIndex];
                } else {
                    entry = &state->secondaryEntries[entryIndex];
                }
                entry->y -= 0x10;
                func_ov101_020c00b8(panel->listId, entryIndex, entry->x, entry->y, state);
            }
        }
        func_ov101_020c082c(panel->listId, state);
        return TRUE;
    }
    if (data_02060500 & 0x40) {
        panel->cursor = panel->itemCount - 1;
        panel->scroll = panel->visibleRows - panel->itemCount;
        entryIndex = panel->entryIndex;
        if (entryIndex >= 0) {
            if (panelIndex == 0) {
                entry = &state->primaryEntries[entryIndex];
            } else {
                entry = &state->secondaryEntries[entryIndex];
            }
            entry->y += (panel->itemCount - 1) * 0x10;
            func_ov101_020c00b8(panel->listId, entryIndex, entry->x, entry->y, state);
        }
        func_ov101_020c082c(panel->listId, state);
        return TRUE;
    }
    return FALSE;
}

