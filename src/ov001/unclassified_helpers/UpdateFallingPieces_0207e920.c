#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 isVisible;
    s32 isMirrored;
    fx32 height;
    void *sprite;
    u16 size;
} FallingPiece;

typedef struct {
    s32 mode;
    void *sprites[4];
    void *frameSprite;
    u8 pad_18[0x20 - 0x18];
    s32 isActive;
    FallingPiece pieces[6];
    s32 spawnTimer;
    s32 spawnIndex;
    fx32 fallSpeed;
} FallingContext;

extern FallingContext *data_ov001_020a04d4;
extern void SpawnFallingPiece_0207e44c(FallingContext *context, FallingPiece *piece);
extern void UpdateFallingPiecePosition_0207e3ec(FallingPiece *piece);
extern void func_ov001_0207e2a8(void);

extern void AlarmCallback_0206ad1c(void *arg);

s32 UpdateFallingPieces_0207e920(void)
{
    FallingContext *context = data_ov001_020a04d4;
    FallingPiece *piece;
    s32 i;

    if (context->isActive != 0) {
        context->spawnTimer--;
        if (context->spawnTimer < 0) {
            context->spawnTimer = 15;
            SpawnFallingPiece_0207e44c(context, &context->pieces[context->spawnIndex]);
            context->spawnIndex = (context->spawnIndex + 1) % 6;
        }
        func_ov001_0207e2a8();
        for (i = 0; i < 6; i++) {
            piece = &context->pieces[i];
            if (piece->isVisible != 0) {
                piece->height -= context->fallSpeed;
                UpdateFallingPiecePosition_0207e3ec(piece);
                AlarmCallback_0206ad1c(piece->sprite);
            }
        }
        AlarmCallback_0206ad1c(context->frameSprite);
    }
    return 0;
}
