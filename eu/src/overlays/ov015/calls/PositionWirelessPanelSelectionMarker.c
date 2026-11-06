#include "nitro/types.h"

extern void PlaySoundEffect(int a, int b);
extern void ResolveWidgetPositionComponents(void *state, u32 param, int *outBuf, int flags);
extern u32 FindWidgetById(void *state, int id);
extern void SetWidgetPosition(void *state, u32 value, int *outBuf, int flags);
extern void SetFocusedWidget(void *state, u32 value);
extern u8 *gWirelessMenuWork;

void PositionWirelessPanelSelectionMarker(u32 param) {
    int outBuf[2];
    u32 value;

    gWirelessMenuWork[0xe0] |= 2;
    ResolveWidgetPositionComponents(gWirelessMenuWork + 0x6ac0, param, outBuf, 0);
    outBuf[0] = outBuf[0] - 0x2c000;
    value = FindWidgetById(gWirelessMenuWork + 0x6ac0, 0xb);
    SetWidgetPosition(gWirelessMenuWork + 0x6ac0, value, outBuf, 0);
    value = FindWidgetById(gWirelessMenuWork + 0x6ac0, 9);
    SetFocusedWidget(gWirelessMenuWork + 0x6ac0, value);
    PlaySoundEffect(2, 1);
}
