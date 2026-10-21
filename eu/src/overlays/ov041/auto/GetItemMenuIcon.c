#include "nitro/types.h"

/* The menu icon of items 0xe7-0xea (0xe1, 0xe2, 0xe3, 0xe3); any other id is returned unchanged. */
int GetItemMenuIcon(int itemId)
{
    switch (itemId) {
    case 0xe7:
        return 0xe1;
    case 0xe8:
        return 0xe2;
    case 0xe9:
    case 0xea:
        return 0xe3;
    }
    return itemId;
}
