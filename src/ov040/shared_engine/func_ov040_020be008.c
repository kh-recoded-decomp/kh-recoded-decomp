#include "nitro/types.h"

extern u8 ***data_ov040_020be264;

u8 *func_ov040_020be008(int index) {
    return *data_ov040_020be264[index] + 8;
}
