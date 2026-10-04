#include "nitro/types.h"

extern int func_020275c8();

int GetRowColorWithStatus_020bf5cc(int row, int cursor, int limit)
{
    if (cursor < 0 || row == cursor) {
        if (row >= limit) {
            return 0xa;
        }
        if (func_020275c8() >= 2) {
            return 0xe;
        }
        return 2;
    }
    if (row < cursor) {
        return 0xc;
    }
    return 8;
}