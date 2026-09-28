#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 currentFrame;
    u8 pad_04[4];
    void *texAnm;
} TexSRTAnimState;

typedef struct {
    u32 flag;
    u8 pad_04[0xc];
    u32 prmTexImage;
} MatAnmResult;

extern void EvaluateTextureSRTAnimation_0201c814(void *pTexAnm, u16 idx, u32 frame, MatAnmResult *pResult);

void EvaluateMaterialTexSRT_0201c9dc(MatAnmResult *result, TexSRTAnimState *state, int idx)
{
    u16 numFrame;
    fx32 frame;

    frame = state->currentFrame;
    numFrame = *(u16 *)((u8 *)state->texAnm + 4);
    if (frame >= (s32)(numFrame * 0x1000)) {
        frame = numFrame * 0x1000 - 1;
    } else if (frame < 0) {
        frame = 0;
    }
    EvaluateTextureSRTAnimation_0201c814(state->texAnm, (u16)idx, frame >> 0xc, result);
    result->prmTexImage = (result->prmTexImage & 0x3fffffff) | 0x40000000;
    result->flag = result->flag | 8;
}
