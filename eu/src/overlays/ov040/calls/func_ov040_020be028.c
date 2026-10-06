#include "nitro/types.h"

extern u8 ***data_ov040_020be284;

u8 *func_ov040_020be028(int index) {
    return *data_ov040_020be284[index] + 8;
}
