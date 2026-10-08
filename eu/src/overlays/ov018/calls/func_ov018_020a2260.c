#include "nitro/types.h"

extern void DestroyEntryGroup(int channel);
extern void func_0202eb08(int *resourceState);

void func_ov018_020a2260(int object)
{
    DestroyEntryGroup((int)*(s16 *)(object + 0x470));
    if (*(int *)(object + 0xd4) != 0) {
        func_0202eb08((int *)(object + 0x138));
    }
    if (*(int *)(object + 0x1d8) != 0) {
        func_0202eb08((int *)(object + 0x23c));
    }
    if (*(int *)(object + 0x2dc) != 0) {
        func_0202eb08((int *)(object + 0x340));
    }
    if (*(int *)(object + 0x3e0) != 0) {
        func_0202eb08((int *)(object + 0x444));
    }
}
