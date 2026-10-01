#include "nitro/types.h"

typedef struct GaugeContext {
    u8 pad_000[0x6c];
    u32 archive;
    u8 pad_070[0x474 - 0x70];
    s16 displayedLevel;
    u16 gauge;
    u32 isMaxed;
    u8 pad_47c[0x4];
    u32 flags;
} GaugeContext;

typedef struct GaugeGlobals {
    u32 unk_00;
    GaugeContext *context;
} GaugeGlobals;

extern GaugeGlobals data_ov001_020a04a4;

extern void func_ov001_0207b548(void);
extern BOOL func_ov001_020728e4(void);
extern u32 func_ov001_02077bcc(void);
extern void func_ov001_020781a4(int id);
extern void *QueueFileLoadRequest_020ba114(u32 path, int loadMode, void (*callback)(void *, void *), void *userData);
extern void func_ov001_0206f040(void *request, void *userData);
extern void BlendIconTiles_0206ed8c(u32 value);

#define LEVEL_FILE(archive, index) ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

void ResetGaugeDisplay_020734f8(void)
{
    GaugeContext *context = data_ov001_020a04a4.context;

    func_ov001_0207b548();
    context->displayedLevel = func_ov001_020728e4() ? 3 : 0;
    context->gauge = 0;
    if (func_ov001_02077bcc() == 13) {
        if (func_ov001_020728e4()) {
            func_ov001_020781a4(7);
        } else {
            func_ov001_020781a4(0);
        }
    }
    context->flags &= ~0x10000;
    if (func_ov001_020728e4()) {
        BlendIconTiles_0206ed8c(context->gauge);
    } else {
        context->flags |= 0x8000;
        QueueFileLoadRequest_020ba114(LEVEL_FILE(context->archive, 5), 1, func_ov001_0206f040, NULL);
    }
    context->isMaxed = 0;
}
