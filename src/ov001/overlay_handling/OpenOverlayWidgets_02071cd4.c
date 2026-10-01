#include "nitro/types.h"

typedef struct OverlayState {
    u8 pad[0x42c];
    void *handle;
    u8 pad430[0x18];
    void *bg3Char;
    void *bg2Char;
    u8 pad450[0xc];
    void *palette;
    u8 pad460[0x20];
    u32 released : 1;
    u32 unk480 : 31;
} OverlayState;

typedef struct OverlayGlobals {
    u32 unk0;
    OverlayState *state;
} OverlayGlobals;

typedef struct TaskParams {
    u16 mode;
    u8 pad[0xe];
} TaskParams;

extern OverlayGlobals data_ov001_020a04a4;
extern char data_ov045_020c0800[];
extern char OVERLAY_45_ID_0000002d[];
extern void func_02029f78(int processor, int overlayId);
extern void func_ov001_0206ec80(void);
extern void SetFieldVisiblePlanes_0206ec3c(void);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char_02007a90(const void *src, u32 offset, u32 size);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void *func_0202a448(void *descriptor, void *userData);

void OpenOverlayWidgets_02071cd4(void)
{
    OverlayState *state = data_ov001_020a04a4.state;
    TaskParams params;

    func_02029f78(0, (int)OVERLAY_45_ID_0000002d);
    params.mode = 2;
    if (state->handle == NULL) {
        state->released = 0;
        func_ov001_0206ec80();
        SetFieldVisiblePlanes_0206ec3c();
        if (state->bg3Char != NULL) {
            GX_LoadBG3Char_02007b70(state->bg3Char, 0, 0x5800);
            GX_LoadBG2Char_02007a90(state->bg2Char, 0, 0x1000);
        }
        if (state->palette != NULL) {
            func_02007250(state->palette, 0, 0x200);
        }
        state->handle = func_0202a448(data_ov045_020c0800, &params);
    }
}
