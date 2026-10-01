#include "nitro/types.h"

int func_0204e588(int object);
int IntArray_Get_020152b0(int *array, int index);

/* Round byte size up to mapping boundary blocks */
u32 DispObj_GetCharBlockCount_0204e5ac(int manager, u8 *image)
{
    u32 blocks;
    u32 size = IntArray_Get_020152b0((int *)(image + 0x38), func_0204e588(manager));
    switch ((*(int *)(image + 0xc) >> 20) & 3) {
    case 0:
        blocks = (size + 0x1f) >> 5;
        break;
    case 1:
        blocks = (size + 0x3f) >> 6;
        break;
    case 2:
        blocks = (size + 0x7f) >> 7;
        break;
    case 3:
        blocks = (size + 0xff) >> 8;
        break;
    }
    return blocks;
}
