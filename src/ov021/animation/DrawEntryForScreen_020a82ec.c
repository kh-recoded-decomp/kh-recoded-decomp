#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x20];
    u8 renderObj[0x5c];
    u16 angleY;
    u16 angleX;
    MtxFx43 matrix;
    VecFx32 position;
    u8 pad_bc[0x54];
} DrawNode;

typedef struct {
    s8 active;
    s8 screen;
    s8 kind;
    u8 pad_03;
    u16 flags;
    u8 pad_06[2];
    DrawNode node;
    fx32 scale;
    MtxFx43 *matrixPtr;
} DrawEntry;

typedef struct {
    u8 pad_00[0x54];
    u32 flags;
} GeometryState;

extern const s16 data_0205356c[];
extern MtxFx33 data_0205a9b8;
extern VecFx32 data_0205a9dc;
extern GeometryState data_0205a9a4;

extern void func_ov021_020a86b0(DrawEntry *entry);
extern void SceneNode_Draw_01ffb12c(DrawNode *node);
extern void *func_ov021_020af5f4(void);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void camera_commit_explicit_projection_0202a8c4(void *camera, fx32 top, fx32 bottom, fx32 left, fx32 right);
extern void camera_commit_projection_0202a814(void *camera);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_02019188(void);
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const void *args, u32 numWords);
extern void func_01ffe1bc(void *renderObj);

void DrawEntryForScreen_020a82ec(DrawEntry *entry, s32 screen)
{
    if (entry->active != 0 && entry->screen == screen) {
        s32 kind = entry->kind;
        if (kind != 3 && (entry->flags & 2)) {
            entry->flags &= ~2;
            return;
        }
        switch (kind) {
        case 0:
        case 1:
            if (kind == 1) {
                func_ov021_020a86b0(entry);
            }
            SceneNode_Draw_01ffb12c(&entry->node);
            return;
        case 4:
        case 5: {
            void *camera = func_ov021_020af5f4();
            fx32 width = FixedPointMultiply12(entry->scale, *(fx32 *)((u8 *)camera + 8));
            if (entry->kind == 5) {
                func_ov021_020a86b0(entry);
            }
            camera_commit_explicit_projection_0202a8c4(camera, entry->scale, -entry->scale, -width, width);
            SceneNode_Draw_01ffb12c(&entry->node);
            camera_commit_projection_0202a814(camera);
            return;
        }
        case 2: {
            int index = entry->node.angleY >> 4;
            MTX_RotY33_01ff923c(&data_0205a9b8, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
            data_0205a9dc = *(VecFx32 *)&entry->node.matrix._30;
            data_0205a9a4.flags &= ~0xa4;
            func_02019188();
            QueueOrSendGeometryCommand_01ffa37c(0x17, entry->matrixPtr, 0xc);
            QueueOrSendGeometryCommand_01ffa37c(0x1b, &entry->node.position, 3);
            func_01ffe1bc(entry->node.renderObj);
            break;
        }
        }
    }
}
