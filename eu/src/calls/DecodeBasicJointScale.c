/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */

#include "nnsys/g3d.h"

void DecodeBasicJointScale(NNSG3dJntAnmResult *result, const fx32 *source,
                           const u8 *unused, u32 flags) {
    if ((flags & 4) != 0) {
        result->flag |= 1;
    } else {
        result->scale.x = source[0];
        result->scale.y = source[1];
        result->scale.z = source[2];
    }

    result->flag |= 0x18;
}
