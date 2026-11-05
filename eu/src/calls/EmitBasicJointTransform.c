#include "nnsys/g3d.h"

extern void NNS_G3dGeBufferOP_N(u32 opcode, const void *payload, u32 wordCount);

void EmitBasicJointTransform(NNSG3dJntAnmResult *result)
{
    u32 flags = result->flag;
    if ((flags & NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO) == 0) {
        if ((flags & NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO) == 0)
            /* Rotation and translation form one contiguous native 4x3 payload. */
            NNS_G3dGeBufferOP_N(0x19, &result->rot, 12);
        else
            NNS_G3dGeBufferOP_N(0x1c, &result->trans, 3);
    } else if ((flags & NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO) == 0) {
        NNS_G3dGeBufferOP_N(0x1a, &result->rot, 9);
    }
    /* Re-read the result flags after sending, as in the original. */
    if ((result->flag & NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE) != 0)
        return;
    NNS_G3dGeBufferOP_N(0x1b, &result->scale, 3);
}
