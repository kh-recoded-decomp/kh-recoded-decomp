#include "nitro/types.h"

/* The effect kind (7, 8 or 9) of a command 0xcb-0xd8; 7 for any other. */
int GetCommandEffectKind(int commandId)
{
    switch (commandId) {
    case 0xcb:
        return 7;
    case 0xcc:
        return 8;
    case 0xcd:
        return 8;
    case 0xd6:
        return 7;
    case 0xd7:
        return 8;
    case 0xd8:
        return 8;
    case 0xce:
        return 7;
    case 0xcf:
        return 8;
    case 0xd3:
        return 8;
    case 0xd4:
        return 9;
    case 0xd5:
        return 9;
    }
    return 7;
}
