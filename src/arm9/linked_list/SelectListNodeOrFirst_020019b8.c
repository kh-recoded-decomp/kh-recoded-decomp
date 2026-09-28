#include "nitro/types.h"

extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);

void SelectListNodeOrFirst_020019b8(void *self, void *target)
{
    void *list = (u8 *)self + 4;
    void *current = NNS_FndGetNextListObject_02012a38(list, 0);
    void *first = current;
    if (target != 0 && current != 0) {
        do {
            if (current == target) {
                break;
            }
            current = NNS_FndGetNextListObject_02012a38(list, current);
        } while (current != 0);
    }
    if (current == 0) {
        current = first;
    }
    *(void **)((u8 *)self + 0x20) = current;
    *(void **)((u8 *)self + 0x10) = (u8 *)current + 0xc;
}
