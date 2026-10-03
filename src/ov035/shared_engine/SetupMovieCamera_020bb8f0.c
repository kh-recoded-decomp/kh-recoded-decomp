#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Mtx33 {
    fx32 m[9];
} Mtx33;

typedef struct GeometryState {
    u8 unknown_00[0x54];
    u32 flags;
} GeometryState;

extern const VecFx32 data_ov035_020bc3fc;
extern const VecFx32 data_ov035_020bc3f0;
extern const Mtx33 data_ov035_020bc424;
extern Mtx33 data_0205a9b8;
extern GeometryState data_0205a9a4;
extern void func_0201931c(const VecFx32 *target);
extern void func_020192ec(const VecFx32 *target);
extern void func_01ff87c4(const Mtx33 *src, Mtx33 *dst);
extern void FlushGeometryState_02019230(void);
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const u32 *args, u32 numWords);

void SetupMovieCamera_020bb8f0(void) {
    u32 command;
    VecFx32 position;
    VecFx32 target;
    Mtx33 rotation;

    position = data_ov035_020bc3fc;
    target = data_ov035_020bc3f0;
    rotation = data_ov035_020bc424;
    func_0201931c(&target);
    func_020192ec(&position);
    func_01ff87c4(&rotation, &data_0205a9b8);
    data_0205a9a4.flags &= ~0xa4;
    FlushGeometryState_02019230();
    command = 0x1f08c0;
    QueueOrSendGeometryCommand_01ffa37c(0x29, &command, 1);
}
