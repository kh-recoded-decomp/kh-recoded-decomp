#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_00[0x4];
    int scrollX;
    u8 pad_08[0x4];
    int scrollY;
    int offsetY;
    int offsetX;
    u8 pad_18[0x18];
    void *paletteA;
    void *paletteB;
} MenuContext;

extern MenuContext *data_ov001_020a04d0;
extern void *func_ov001_0207123c(void);
extern void *GetSceneTagTracker_020711b0(void);
extern void func_ov027_020b9d54(void *widgets, int layer, int x, int y, int width, int height);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern int GFXi_EnqueueCommand_02014090(int command, int offset, void *data, int size);

void ResetMenuScreenLayers_0207de48(void)
{
    MenuContext *context = data_ov001_020a04d0;
    void *widgets = func_ov001_0207123c();
    void *pool = GetSceneTagTracker_020711b0();

    context->scrollX = 0;
    context->scrollY = 0;
    context->offsetX = 0;
    context->offsetY = 0;
    func_ov027_020b9d54(widgets, 0xb, 0xe, 0, 4, 2);
    func_ov027_020b9d54(widgets, 0xb, 0xf, 0x13, 2, 3);
    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 300));
    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 308));
    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 302));
    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 305));
    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 306));
    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 307));
    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 311));
    *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & ~3) | 2);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & ~3) | 1);
    GFXi_EnqueueCommand_02014090(0xf, 0x1a0, context->paletteA, 0x20);
    GFXi_EnqueueCommand_02014090(0xf, 0x1c0, context->paletteB, 0x20);
}
