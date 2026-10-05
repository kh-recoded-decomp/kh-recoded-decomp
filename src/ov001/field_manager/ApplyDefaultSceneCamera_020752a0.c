#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx33 {
    fx32 m[9];
} MtxFx33;

typedef struct GlobalStateTail {
    u8 pad_00[0x54];
    u32 flags;
} GlobalStateTail;

extern const VecFx32 data_ov001_0209de88;
extern const VecFx32 data_ov001_0209de94;
extern const MtxFx33 data_ov001_0209dec0;
extern GlobalStateTail data_0205a9a4;
extern MtxFx33 data_0205a9b8;

extern void func_0201931c(const VecFx32 *vec);
extern void func_020192ec(const VecFx32 *vec);
extern void func_01ff87c4(const MtxFx33 *src, MtxFx33 *dst);
extern void FlushGeometryState_02019230(void);
extern void QueueOrSendGeometryCommand_01ffa37c(int command, const u32 *params, int count);

void ApplyDefaultSceneCamera_020752a0(void)
{
    VecFx32 second = data_ov001_0209de88;
    VecFx32 first = data_ov001_0209de94;
    MtxFx33 rotation = data_ov001_0209dec0;
    u32 command;

    func_0201931c(&first);
    func_020192ec(&second);
    func_01ff87c4(&rotation, &data_0205a9b8);
    data_0205a9a4.flags &= ~0xa4;
    FlushGeometryState_02019230();
    command = 0x1f00c0;
    QueueOrSendGeometryCommand_01ffa37c(0x29, &command, 1);
}
