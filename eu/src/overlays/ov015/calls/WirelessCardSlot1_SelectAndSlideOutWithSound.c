#include "nitro/types.h"

extern void PlaySoundEffect(int a, int b);
extern void SelectWidgetAndSlideOut(void);

void WirelessCardSlot1_SelectAndSlideOutWithSound(void) {
    SelectWidgetAndSlideOut();
    PlaySoundEffect(2, 1);
}
