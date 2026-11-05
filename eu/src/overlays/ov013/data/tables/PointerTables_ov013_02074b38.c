#include "nitro/types.h"

extern void Ov013Scroll_LeavePhase0Noop(void);
extern void LoadPanelPaletteBase(void); /* LoadPanelPaletteBase */
extern void ScrollPanelSlotsUp(void); /* ScrollPanelSlotsUp */
extern void Ov013Scroll_LeaveUpNoop(void);
extern void SetPanelScrollDownDirection(void);
extern void ScrollPanelSlotsDown(void); /* ScrollPanelSlotsDown */
extern void Ov013Scroll_LeaveDownNoop(void);
extern void Ov013Scroll_Phase0UpdateNoop(void);

void (*gPanelScrollHandlers[7])(void) = {
    Ov013Scroll_LeavePhase0Noop,
    LoadPanelPaletteBase, /* LoadPanelPaletteBase */
    ScrollPanelSlotsUp, /* ScrollPanelSlotsUp */
    Ov013Scroll_LeaveUpNoop,
    SetPanelScrollDownDirection,
    ScrollPanelSlotsDown, /* ScrollPanelSlotsDown */
    Ov013Scroll_LeaveDownNoop,
};

void (*gPanelScrollInitCallback[1])(void) = {
    Ov013Scroll_Phase0UpdateNoop,
};
