#include "nitro/types.h"

int GetStageKindSoundArc(int id)
{
    switch (id) {
    case 0:
        return 0xd0;
    case 0x11:
        return 0xea;
    case 0x12:
        return 0xef;
    case 0x16:
        return 0xff;
    case 0x17:
        return 0xff;
    case 0x18:
        return 0xff;
    case 0x19:
        return 0xff;
    case 0x1a:
        return 0xff;
    case 0xfd:
        return 0x43;
    }
    return 0;
}
