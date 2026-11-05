#include "nitro/types.h"

extern void DrawFieldMenuOrPartyGaugeFrames(void);
extern void UpdateGaugeFrameState(void); /* UpdateGaugeFrameState */
extern void DrawFieldMenuSlots(void); /* DrawFieldMenuSlots */
extern void DrawFieldMenuSlotsAlt(void); /* DrawFieldMenuSlotsAlt */
extern void RefreshFieldMenuSlots(void); /* RefreshFieldMenuSlots */
extern void RefreshFieldMenuSlotsWrapped(void); /* RefreshFieldMenuSlotsWrapped */

void (*gFieldMenuDrawHandlers[6])(void) = {
    DrawFieldMenuOrPartyGaugeFrames,
    UpdateGaugeFrameState, /* UpdateGaugeFrameState */
    DrawFieldMenuSlots, /* DrawFieldMenuSlots */
    DrawFieldMenuSlotsAlt, /* DrawFieldMenuSlotsAlt */
    RefreshFieldMenuSlots, /* RefreshFieldMenuSlots */
    RefreshFieldMenuSlotsWrapped, /* RefreshFieldMenuSlotsWrapped */
};
