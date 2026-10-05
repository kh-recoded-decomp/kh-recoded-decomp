#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x354];
    void *resource;
    void *handles[1];
} SlotWork;

extern u8 *data_ov035_020bc4e0;
extern void func_ov041_020bde50(int index, int arg, void *resource, u8 first, u8 second);

void OpenSlotHandleIfEmpty(int index, int arg) {
    SlotWork *work = *(SlotWork **)(data_ov035_020bc4e0 + 0xb8);
    void *resource = work->resource;

    if (work->handles[index] == NULL) {
        u8 first = index * 2;
        func_ov041_020bde50(index, arg, resource, first, first + 1);
    }
}
