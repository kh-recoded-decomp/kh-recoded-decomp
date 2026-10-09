#include "src/overlays/ov101/ScrollPanelState.h"

extern void func_ov101_020c082c(int listId, Ov101ScrollPanelState *state);

BOOL ScrollPanelPageDown(int panelIndex, Ov101ScrollPanelState *state)
{
    ScrollPanel *panel = &state->panels[panelIndex];
    int maxScroll;
    int nextScroll;

    nextScroll = panel->scroll;
    if (nextScroll == panel->totalRows - panel->pageRows) {
        return FALSE;
    }
    nextScroll += panel->pageRows;
    if (panel->cursorEntry < 0) {
        panel->cursor = panel->pageRows - 1;
    }
    maxScroll = panel->totalRows - panel->pageRows;
    if (nextScroll > maxScroll) {
        panel->scroll = maxScroll;
    } else {
        panel->scroll = nextScroll;
    }
    func_ov101_020c082c(panel->listId, state);
    return TRUE;
}
