#include "nnsys/g3d.h"

extern void QueueOrSendGeometryCommandPair(int operation, unsigned char encodedByte);

void HandleSbcMatrixRestore(NNSG3dRS *state)
{
    u32 flags = state->flag;

    if ((flags & 0x200) == 0 && (flags & 1) != 0 && (flags & 0x100) == 0) {
        QueueOrSendGeometryCommandPair(0x14, state->c[1]);
    }
    state->c += 2;
}
