#include "nitro/types.h"

u32 func_ov040_020bdc24(u32 code)
{
    u32 mapped;

    mapped = 0xffffffff;
    switch (code) {
    case 0x1e0:
        mapped = 0xcb;
        break;
    case 0x1e1:
        mapped = 0xcc;
        break;
    case 0x1e2:
        mapped = 0xcd;
        break;
    case 0x1e3:
        mapped = 0xce;
        break;
    case 0x1e4:
        mapped = 0xcf;
        break;
    case 0x1e5:
        mapped = 0xd0;
        break;
    case 0x1e6:
        mapped = 0xd1;
        break;
    case 0x1e7:
        mapped = 0xd2;
        break;
    case 0x1e8:
        mapped = 0xd3;
        break;
    case 0x1e9:
        mapped = 0xd4;
        break;
    case 0x1ea:
        mapped = 0xd5;
        break;
    case 0x1eb:
        mapped = 0xd6;
        break;
    case 0x1ec:
        mapped = 0xd7;
        break;
    case 0x1ed:
        mapped = 0xd8;
    }
    return mapped;
}
