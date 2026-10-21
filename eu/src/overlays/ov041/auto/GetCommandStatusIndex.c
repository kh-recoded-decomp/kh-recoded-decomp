#include "nitro/types.h"

/* The entry status a command 0xcb-0xd8 inflicts (0xd0-0xd3 inflict none), or -1. */
int GetCommandStatusIndex(int commandId)
{
    int index = -1;

    switch (commandId) {
    case 0xcb:
        index = 0;
        break;
    case 0xcc:
        index = 2;
        break;
    case 0xcd:
        index = 1;
        break;
    case 0xd6:
        index = 8;
        break;
    case 0xd7:
        index = 9;
        break;
    case 0xd8:
        index = 10;
        break;
    case 0xce:
        index = 3;
        break;
    case 0xcf:
        index = 4;
        break;
    case 0xd4:
        index = 6;
        break;
    case 0xd5:
        index = 7;
        break;
    }
    return index;
}
