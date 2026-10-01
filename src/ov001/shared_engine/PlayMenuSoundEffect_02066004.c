#include "nitro/types.h"

extern void PlaySoundChecked_0204d8d0(void *handle, int sound);

void PlayMenuSoundEffect_02066004(int kind)
{
    int sound;

    switch (kind) {
    case 0:
        sound = 0xf;
        break;
    case 4:
        sound = 0x41;
        break;
    case 1:
        sound = 0x11;
        break;
    case 6:
        sound = 0x10;
        break;
    case 2:
        sound = 0x46;
        break;
    case 3:
        sound = 0x47;
        break;
    case 5:
        sound = 0x48;
        break;
    default:
        return;
    }
    PlaySoundChecked_0204d8d0(NULL, sound);
}
