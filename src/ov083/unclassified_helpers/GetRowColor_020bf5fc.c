#include "nitro/types.h"

int GetRowColor_020bf5fc(int row, int cursor)
{
    if (cursor < 0 || row == cursor) {
        return 2;
    }
    if (row < cursor) {
        return 0xc;
    }
    return 8;
}