#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    u32 scale;
} ModelScaleInfo;

typedef struct {
    u8 pad_00[0x20];
    u8 transform[0xf0];
    void *matrix;
} AttachedModel;

typedef struct {
    u32 flags;
    u32 pad_04;
    u16 drawFlags;
    u8 pad_0a[0x1e];
    u8 transform[4];
    ModelScaleInfo *scaleInfo;
    u8 pad_30[0xd4];
    u16 colorScale;
    u8 pad_106[0xa];
    void *matrix;
    u8 pad_114[0x114];
    AttachedModel *attached;
} DrawnModel;

extern void QueueOrSendGeometryCommand_01ffa37c(int command, const void *data, int words);
extern void func_02019188(void);
extern void setMaterialColorScale_01fff67c(u16 scale);
extern void func_01ffe1bc(void *transform);

void DrawModelWithAttachment_020a9af0(DrawnModel *model)
{
    u32 scale[3];
    AttachedModel *attached;
    u32 value;

    if ((model->flags & 1) && (model->flags & 2)) {
        value = model->scaleInfo->scale;
        scale[0] = value;
        scale[1] = value;
        scale[2] = value;
        QueueOrSendGeometryCommand_01ffa37c(0x1b, scale, 3);
        func_02019188();
        if (model->drawFlags & 0x40) {
            setMaterialColorScale_01fff67c(model->colorScale);
        }
        QueueOrSendGeometryCommand_01ffa37c(0x17, model->matrix, 0xc);
        func_01ffe1bc(model->transform);
        if (model->flags & 0x400) {
            attached = model->attached;
            func_02019188();
            QueueOrSendGeometryCommand_01ffa37c(0x17, attached->matrix, 0xc);
            func_01ffe1bc(attached->transform);
        }
    }
}
