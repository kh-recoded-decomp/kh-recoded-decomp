#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov035_020bc4e0;
extern fx32 data_ov041_020cf80c[][6];
extern fx32 data_ov041_020cf79c[][3];

void GetStageGridPosition_020c2b5c(VecFx32 *out, int column, int row) {
    u8 stage = *(*(u8 **)(data_ov035_020bc4e0 + 0xb8) + 0x348);
    VecFx32 pos;

    pos.x = data_ov041_020cf80c[stage][column];
    pos.y = 0;
    pos.z = data_ov041_020cf79c[stage][row];
    *out = pos;
}
