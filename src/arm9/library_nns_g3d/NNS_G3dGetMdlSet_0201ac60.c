#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/g3d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

NNSG3dResMdlSet * NNS_G3dGetMdlSet_0201ac60 (const NNSG3dResFileHeader * header)
{
    u32 * blks;

    blks = (u32 *)((u8 *)header + header->headerSize);
    return (NNSG3dResMdlSet *)((u8 *)header + blks[0]);
}
