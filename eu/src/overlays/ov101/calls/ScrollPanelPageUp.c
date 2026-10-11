#include "src/overlays/ov101/ScrollPanelState.h"

extern void UpdateScrollPanel(int listId, Ov101ScrollPanelState *state);

BOOL ScrollPanelPageUp(int panelIndex, Ov101ScrollPanelState *state)
{
    ScrollPanel *panel = &state->panels[panelIndex];
    int nextScroll;

    if (panel->scroll == 0) {
        return FALSE;
    }
    nextScroll = panel->scroll - panel->pageRows;
    if (panel->cursorEntry < 0) {
        panel->cursor = 0;
    }
    if (nextScroll < 0) {
        panel->scroll = 0;
    } else {
        panel->scroll = nextScroll;
    }
    UpdateScrollPanel(panel->listId, state);
    return TRUE;
}
