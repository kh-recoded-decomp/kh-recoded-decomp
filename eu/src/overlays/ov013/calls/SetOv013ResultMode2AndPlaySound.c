#include "nitro/types.h"

extern int gOv013PanelGlobals;
extern void PlaySoundEffect(int value, int flag);

void SetOv013ResultMode2AndPlaySound(void) {
    *(u8 *)(gOv013PanelGlobals + 3) = 2;
    PlaySoundEffect(2, 1);
}
