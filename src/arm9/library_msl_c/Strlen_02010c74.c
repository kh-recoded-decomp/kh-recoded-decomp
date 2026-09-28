#include "nitro/types.h"

int Strlen_02010c74(u32 str)
{
    int length;
    u32 *word;

    length = 0;
    while ((str + length) & 3) {
        if (*(char *)(str + length) == 0) {
            return length;
        }
        length++;
    }

    word = (u32 *)(str + length);
    for (;;) {
        u32 combined;
        combined = (*word & 0x7f7f7f7f) + 0x7f7f7f7f | *word | 0x7f7f7f7f;
        combined = ~combined;
        if (combined != 0) {
            break;
        }
        word++;
        length += 4;
    }

    while (*(char *)(str + length) != 0) {
        length++;
    }

    return length;
}
